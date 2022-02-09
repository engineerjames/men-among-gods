#include "MapDisplay.h"

#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>

#include "ConstantIdentifiers.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "Map.h"
#include "PlayerData.h"
#include "TickBuffer.h"
#include "UtilityFunctions.h"

// Commands
#include "LookCommand.h"
#include "MoveCommand.h"
#include "TurnCommand.h"

namespace
{
int autohide( int x, int y )
{
  if ( x >= ( TILEX / 2 ) || ( y <= TILEX / 2 ) )
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int facing( int x, int y, int dir )
{
  if ( dir == 1 && x == TILEX / 2 + 1 && y == TILEY / 2 )
  {
    return 1;
  }
  if ( dir == 2 && x == TILEX / 2 - 1 && y == TILEY / 2 )
  {
    return 1;
  }
  if ( dir == 4 && x == TILEX / 2 && y == TILEY / 2 + 1 )
  {
    return 1;
  }
  if ( dir == 3 && x == TILEX / 2 && y == TILEY / 2 - 1 )
  {
    return 1;
  }

  return 0;
}

} // namespace

namespace MenAmongGods
{

MapDisplay::MapDisplay( MenAmongGods::Map& map, const PlayerData& playerData, const GraphicsCache& cache, const GraphicsIndex& index,
                        const sf::RenderWindow& window )
    : MenAmongGods::Component()
    , map_( map )
    , playerData_( playerData )
    , cache_( cache )
    , index_( index )
    , window_( window )
    , spritesToDraw_()
    , tileType_()
    , tileX_()
    , tileY_()
{
}

void MapDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( const auto& tile : spritesToDraw_ )
  {
    target.draw( tile, states );
  }
}

int MapDisplay::getMapIndexFromMousePosition( const sf::Vector2f& mousePosition, bool setTileOutline )
{
  sf::Vector2f shiftedMousePosition = sf::Vector2f { mousePosition.x + ( 176 - 16 ), mousePosition.y + 8 };

  int mx = 2 * shiftedMousePosition.y + shiftedMousePosition.x - ( YPOS * 2 ) - XPOS + ( ( TILEX - 34 ) / 2 * 32 );
  int my = shiftedMousePosition.x - 2 * shiftedMousePosition.y + ( YPOS * 2 ) - XPOS + ( ( TILEX - 34 ) / 2 * 32 );

  mx /= 32;
  my /= 32;

  if ( setTileOutline )
  {
    tileType_ = 0;
    tileX_    = mx;
    tileY_    = my;
  }

  // Map index
  return mx + my * TILEX;
}

void MapDisplay::finalize()
{
}

void MapDisplay::onUserInput( const sf::Event& e )
{
  // User attempts to move by left clicking on the map
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    // Attempting to port similar logic from inter.c::mouse_mapbox()
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    int m = getMapIndexFromMousePosition( mousePosition, true );

    commands_.emplace_back( std::make_shared< MenAmongGods::MoveCommand >( map_.getMap()[ m ].x, map_.getMap()[ m ].y ) );
  }

  // User faces his/her character a specific direction via a right mouse button click
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Right )
  {
    // Attempting to port similar logic from inter.c::mouse_mapbox()
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    int m = getMapIndexFromMousePosition( mousePosition, false );

    commands_.emplace_back( std::make_shared< MenAmongGods::TurnCommand >( map_.getMap()[ m ].x, map_.getMap()[ m ].y ) );
  }
}

void MapDisplay::update()
{
  map_.lock();

  spritesToDraw_.clear();

  int x {};
  int y {};
  int tmp {};
  int selected_visible {};
  int alpha {};
  int alphastr {};
  int hightlight {};
  int selected_char {};

  int xoff       = -map_.getMap()[ ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX ].obj_xoff - 176; //-176;
  int yoff       = -map_.getMap()[ ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX ].obj_yoff;       //-176;
  int plr_sprite = map_.getMap()[ ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX ].obj2;

  ( void ) plr_sprite;
  ( void ) selected_visible;

  for ( y = TILEY - 1; y >= 0; y-- )
  {
    for ( x = 0; x < TILEX; x++ )
    {
      // background
      int m = x + y * MAPX;

      if ( hightlight == HL_MAP && tileType_ == 0 && tileX_ == x && tileY_ == y )
      {
        tmp = 16;
      }
      else
      {
        tmp = 0;
      }
      if ( map_.getMap()[ m ].flags & INVIS )
      {
        tmp |= 64;
      }
      if ( map_.getMap()[ m ].flags & INFRARED )
      {
        tmp |= 256;
      }
      if ( map_.getMap()[ m ].flags & UWATER )
      {
        tmp |= 512;
      }

      // Most of the floor tiles are 32x32 images
      // The tile itself is on the lower portion of the image
      // 32 px wide and 22px tall approximately
      // xs / ys are the x and y size in tiles (width / 32), and height / 32 respectively

      // What is the difference between ba_sprite and back? Can I always use ba_sprite?
      // by using ba_sprite instead; we fixed the intermittent "blank" sprite issue
      copysprite( map_.getMap()[ m ].back, map_.getMap()[ m ].light | tmp, x * 32, y * 32, xoff, yoff );

      if ( playerData_.getGotoPosition().x == map_.getMap()[ m ].x && playerData_.getGotoPosition().y == map_.getMap()[ m ].y )
      {
        copysprite( 31, 0, x * 32, y * 32, xoff, yoff );
      }
    }
  }

  for ( y = TILEY - 1; y >= 0; y-- )
  {
    for ( x = 0; x < TILEX; x++ )
    {
      int m = x + y * MAPX;

      if ( map_.getMap()[ x + y * MAPX ].flags & INVIS )
      {
        tmp = 128;
      }
      else
      {
        tmp = 0;
      }

      if ( map_.getMap()[ m ].flags & INFRARED )
      {
        tmp |= 256;
      }
      if ( map_.getMap()[ m ].flags & UWATER )
      {
        tmp |= 512;
      }

      // object
      if ( playerData_.areWallsHidden() == 0 || ( map_.getMap()[ m ].flags & ISITEM ) || autohide( x, y ) )
      {
        int tmp2 {};
        ( void ) tmp2;

        if ( map_.getMap()[ m ].obj1 > 16335 && map_.getMap()[ m ].obj1 < 16422 && map_.getMap()[ m ].obj1 != 16357 &&
             map_.getMap()[ m ].obj1 != 16365 && map_.getMap()[ m ].obj1 != 16373 && map_.getMap()[ m ].obj1 != 16381 &&
             map_.getMap()[ m ].obj1 != 16357 && map_.getMap()[ m ].obj1 != 16389 && map_.getMap()[ m ].obj1 != 16397 &&
             map_.getMap()[ m ].obj1 != 16405 && map_.getMap()[ m ].obj1 != 16413 && map_.getMap()[ m ].obj1 != 16421 &&
             ! facing( x, y, playerData_.getPlayerDirection() ) && ! autohide( x, y ) && playerData_.areWallsHidden() )
        { // mine hack
          if ( map_.getMap()[ m ].obj1 < 16358 )
          {
            tmp2 = 457;
          }
          else if ( map_.getMap()[ m ].obj1 < 16366 )
          {
            tmp2 = 456;
          }
          else if ( map_.getMap()[ m ].obj1 < 16374 )
          {
            tmp2 = 455;
          }
          else if ( map_.getMap()[ m ].obj1 < 16382 )
          {
            tmp2 = 466;
          }
          else if ( map_.getMap()[ m ].obj1 < 16390 )
          {
            tmp2 = 459;
          }
          else if ( map_.getMap()[ m ].obj1 < 16398 )
          {
            tmp2 = 458;
          }
          else if ( map_.getMap()[ m ].obj1 < 16398 )
          {
            tmp2 = 449;
          }
          else if ( map_.getMap()[ m ].obj1 < 16406 )
          {
            tmp2 = 468;
          }
          else
          {
            tmp2 = 467;
          }

          if ( hightlight == HL_MAP && tileType_ == 1 && tileX_ == x && tileY_ == y )
          {
            copysprite( tmp2, map_.getMap()[ m ].light | 16 | tmp, x * 32, y * 32, xoff, yoff );
          }
          else
          {
            copysprite( tmp2, map_.getMap()[ m ].light | tmp, x * 32, y * 32, xoff, yoff );
          }
        }
        else
        {
          if ( hightlight == HL_MAP && tileType_ == 1 && tileX_ == x && tileY_ == y )
          {
            copysprite( map_.getMap()[ m ].obj1, map_.getMap()[ m ].light | 16 | tmp, x * 32, y * 32, xoff, yoff );
          }
          else
          {
            copysprite( map_.getMap()[ m ].obj1, map_.getMap()[ m ].light | tmp, x * 32, y * 32, xoff, yoff );
          }
        }
      }
      else if ( map_.getMap()[ m ].obj1 )
      {
        copysprite( map_.getMap()[ m ].obj1 + 1, map_.getMap()[ m ].light | tmp, x * 32, y * 32, xoff, yoff );
      }

      // character
      if ( tileType_ == 2 && tileX_ == x && tileY_ == y )
      {
        tmp = 16;
      }
      else
      {
        tmp = 0;
      }

      if ( map_.getMap()[ m ].ch_nr == selected_char )
      {
        tmp |= 32;
        selected_visible = 1;
      }

      if ( map_.getMap()[ m ].flags & INVIS )
      {
        tmp |= 64;
      }
      if ( map_.getMap()[ m ].flags & STONED )
      {
        tmp |= 128;
      }
      if ( map_.getMap()[ m ].flags & INFRARED )
      {
        tmp |= 256;
      }
      if ( map_.getMap()[ m ].flags & UWATER )
      {
        tmp |= 512;
      }

      //   if ( do_shadow )
      //     {
      //     // dd_shadow( map_.getMap()[ m ].obj2, x * 32, y * 32, xoff + map_.getMap()[ m ].obj_xoff, yoff + map_.getMap()[ m ].obj_yoff
      //     + 4 );
      //     }
      if ( map_.getMap()[ m ].obj2 != 0 )
      {
        copysprite( map_.getMap()[ m ].obj2, map_.getMap()[ m ].light | tmp, x * 32, y * 32, xoff + map_.getMap()[ m ].obj_xoff,
                    yoff + map_.getMap()[ m ].obj_yoff );
      }

      if ( playerData_.getAttackTarget() != 0 && playerData_.getAttackTarget() == map_.getMap()[ m ].ch_nr )
      {
        copysprite( 34, 0, x * 32, y * 32, xoff + map_.getMap()[ m ].obj_xoff, yoff + map_.getMap()[ m ].obj_yoff );
      }

      if ( playerData_.getPlayerAction() == DR_GIVE && playerData_.getFirstTarget() == map_.getMap()[ m ].ch_id )
      {
        copysprite( 45, 0, x * 32, y * 32, xoff + map_.getMap()[ m ].obj_xoff, yoff + map_.getMap()[ m ].obj_yoff );
      }

      if ( ( playerData_.clientShouldShowNames() | playerData_.clientShouldShowPercentHealth() ) && map_.getMap()[ m ].ch_nr )
      {
        // set_look_proz( map_.getMap()[ m ].ch_nr, map_.getMap()[ m ].ch_id, map_.getMap()[ m ].ch_proz );
        // dd_gputtext( x * 32, y * 32, 1, lookup( map_.getMap()[ m ].ch_nr, map_.getMap()[ m ].ch_id ), xoff + map_.getMap()[ m
        // ].obj_xoff,
        //              yoff + map_.getMap()[ m ].obj_yoff );
      }

      if ( playerData_.getPlayerAction() == DR_DROP && playerData_.getFirstTarget() == map_.getMap()[ m ].x &&
           playerData_.getSecondTarget() == map_.getMap()[ m ].y )
      {
        copysprite( 32, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( playerData_.getPlayerAction() == DR_PICKUP && playerData_.getFirstTarget() == map_.getMap()[ m ].x &&
           playerData_.getSecondTarget() == map_.getMap()[ m ].y )
      {
        copysprite( 33, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( playerData_.getPlayerAction() == DR_USE && playerData_.getFirstTarget() == map_.getMap()[ m ].x &&
           playerData_.getSecondTarget() == map_.getMap()[ m ].y )
      {
        copysprite( 45, 0, x * 32, y * 32, xoff, yoff );
      }

      // effects
      if ( map_.getMap()[ m ].flags2 & MF_MOVEBLOCK )
      {
        copysprite( 55, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_SIGHTBLOCK )
      {
        copysprite( 84, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_INDOORS )
      {
        copysprite( 56, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_UWATER )
      {
        copysprite( 75, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_NOMONST )
      {
        copysprite( 59, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_BANK )
      {
        copysprite( 60, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_TAVERN )
      {
        copysprite( 61, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_NOMAGIC )
      {
        copysprite( 62, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_DEATHTRAP )
      {
        copysprite( 73, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_NOLAG )
      {
        copysprite( 57, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_ARENA )
      {
        copysprite( 76, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & MF_NOEXPIRE )
      {
        copysprite( 82, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getMap()[ m ].flags2 & 0x80000000 )
      {
        copysprite( 72, 0, x * 32, y * 32, xoff, yoff );
      }

      if ( ( map_.getMap()[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == INJURED )
      {
        copysprite( 1079, 0, x * 32, y * 32, xoff + map_.getMap()[ m ].obj_xoff, yoff + map_.getMap()[ m ].obj_yoff );
      }
      if ( ( map_.getMap()[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 ) )
      {
        copysprite( 1080, 0, x * 32, y * 32, xoff + map_.getMap()[ m ].obj_xoff, yoff + map_.getMap()[ m ].obj_yoff );
      }
      if ( ( map_.getMap()[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED2 ) )
      {
        copysprite( 1081, 0, x * 32, y * 32, xoff + map_.getMap()[ m ].obj_xoff, yoff + map_.getMap()[ m ].obj_yoff );
      }
      if ( ( map_.getMap()[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 | INJURED2 ) )
      {
        copysprite( 1082, 0, x * 32, y * 32, xoff + map_.getMap()[ m ].obj_xoff, yoff + map_.getMap()[ m ].obj_yoff );
      }

      if ( map_.getMap()[ m ].flags & DEATH )
      {
        if ( map_.getMap()[ m ].obj2 )
        {
          copysprite( 280 + ( ( map_.getMap()[ m ].flags & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff + map_.getMap()[ m ].obj_xoff,
                      yoff + map_.getMap()[ m ].obj_yoff );
        }
        else
        {
          copysprite( 280 + ( ( map_.getMap()[ m ].flags & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff, yoff );
        }
      }
      if ( map_.getMap()[ m ].flags & TOMB )
      {
        copysprite( 240 + ( ( map_.getMap()[ m ].flags & TOMB ) >> 12 ) - 1, map_.getMap()[ m ].light, x * 32, y * 32, xoff, yoff );
      }

      alpha    = 0;
      alphastr = 0;

      if ( map_.getMap()[ m ].flags & EMAGIC )
      {
        alpha |= 1;
        alphastr = std::max( ( unsigned ) alphastr, ( ( map_.getMap()[ m ].flags & EMAGIC ) >> 22 ) );
      }

      if ( map_.getMap()[ m ].flags & GMAGIC )
      {
        alpha |= 2;
        alphastr = std::max( ( unsigned ) alphastr, ( ( map_.getMap()[ m ].flags & GMAGIC ) >> 25 ) );
      }

      if ( map_.getMap()[ m ].flags & CMAGIC )
      {
        alpha |= 4;
        alphastr = std::max( ( unsigned ) alphastr, ( ( map_.getMap()[ m ].flags & CMAGIC ) >> 28 ) );
      }
      if ( alpha )
      {
        // dd_alphaeffect_magic( alpha, alphastr, x * 32, y * 32, xoff + map_.getMap()[ m ].obj_xoff, yoff + map_.getMap()[ m ].obj_yoff
        // );
      }
    }
  }

  // eng_display_win( plr_sprite, init );

  // ********************
  // display cursors etc.
  // ********************

  //   if ( init && pl.citem )
  //   {
  //     if ( cursor_type == CT_DROP || cursor_type == CT_SWAP || cursor_type == CT_USE )
  //       copyspritex( pl.citem, mouse_x - 16, mouse_y - 16, 16 );
  //     else
  //       copyspritex( pl.citem, mouse_x - 16, mouse_y - 16, 0 );
  //   }
  sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

  if ( mousePosition.x > 0 && mousePosition.y > 0 )
  {
    for ( auto& tile : spritesToDraw_ )
    {
      if ( tile.getGlobalBounds().contains( mousePosition ) )
      {
        tile.setColor( sf::Color { 255, 255, 255, 200 } );
        break;
      }
    }
  }
  map_.unlock();
}

void MapDisplay::loadFromFile( std::string filePath )
{
  std::ifstream                 mapFile( filePath );
  boost::archive::text_iarchive ia( mapFile );

  cmap tmpMap {};
  if ( mapFile.is_open() )
  {
    for ( unsigned int x = 0; x < MAPX; ++x )
    {
      for ( unsigned int y = 0; y < MAPY; ++y )
      {
        ia >> tmpMap;
        map_.getMap()[ x + y * MAPX ] = tmpMap;
      }
    }
  }

  mapFile.close();
}

void MapDisplay::copysprite( int nr, int effect, int xpos, int ypos, int xoff, int yoff )
{
  if ( nr == 0 )
  {
    return;
  }

  // xs / ys are the x and y size in tiles (width / 32), and height / 32 respectively
  GraphicsIndex::Index gfxIndex = index_.getIndex( nr );
  unsigned char        xs       = gfxIndex.xs / 32;
  unsigned char        ys       = gfxIndex.ys / 32;

  unsigned int rx = ( xpos / 2 ) + ( ypos / 2 ) - ( xs * 16 ) + 32 + XPOS - ( ( TILEX - 34 ) / 2 * 32 );
  if ( xpos < 0 && ( xpos & 1 ) )
  {
    rx--;
  }
  if ( ypos < 0 && ( ypos & 1 ) )
  {
    rx--;
  }

  unsigned int ry = ( xpos / 4 ) - ( ypos / 4 ) + YPOS - ys * 32;

  if ( xpos < 0 && ( xpos & 3 ) )
  {
    ry--;
  }
  if ( ypos < 0 && ( ypos & 3 ) )
  {
    ry++;
  }

  rx += xoff;
  ry += yoff;

  for ( unsigned int y = 0; y < 1; y++ )
  {
    for ( unsigned int x = 0; x < 1; x++ ) // TODO: Why does only `1` work here, vs. the legacy xs ys values?
    {
      // This is where we have all the data we need now to copy sprites out to a.. draw list?
      spritesToDraw_.push_back( cache_.getSprite( nr ) );
      sf::Sprite& newSprite = *( spritesToDraw_.end() - 1 );
      newSprite.setPosition( sf::Vector2f { static_cast< float >( rx + x * 32 ), static_cast< float >( ry + y * 32 ) } );
      ( void ) effect;
    }
  }
}

void MapDisplay::saveToFile() const
{
  std::ofstream                 mapFile( "mapfile.archive" );
  boost::archive::text_oarchive oa { mapFile };
  if ( mapFile.is_open() )
  {
    for ( unsigned int x = 0; x < MAPX; ++x )
    {
      for ( unsigned int y = 0; y < MAPY; ++y )
      {
        oa << map_.getMap()[ x + y * MAPX ];
      }
    }
  }
  mapFile.close();
}

} // namespace MenAmongGods