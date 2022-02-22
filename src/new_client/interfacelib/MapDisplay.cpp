#include "MapDisplay.h"

#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>
#include <set>

#include "ColorPalette.h"
#include "ConstantIdentifiers.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "Map.h"
#include "PlayerData.h"
#include "TickBuffer.h"
#include "UtilityFunctions.h"

// Commands
#include "AttackCommand.h"
#include "DropCommand.h"
#include "LookCommand.h"
#include "MoveCommand.h"
#include "PickupCommand.h"
#include "TurnCommand.h"
#include "UseCommand.h"

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

MapDisplay::MapDisplay( const sf::Font& font, MenAmongGods::Map& map, PlayerData& playerData, const GraphicsCache& cache,
                        const GraphicsIndex& index, const sf::RenderWindow& window )
    : MenAmongGods::Component()
    , font_( font )
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

  for ( const auto& text : textToDraw_ )
  {
    target.draw( text, states );
  }
}

int MapDisplay::getMapIndexFromMousePosition( const sf::Vector2f& mousePosition, bool setTileOutline )
{
  sf::Vector2f shiftedMousePosition = sf::Vector2f { mousePosition.x + ( 176 - 16 ), mousePosition.y + 8 };

  int mx = static_cast< int >( 2 * shiftedMousePosition.y + shiftedMousePosition.x - ( YPOS * 2 ) - XPOS + ( ( TILEX - 34 ) / 2 * 32 ) );
  int my = static_cast< int >( shiftedMousePosition.x - 2 * shiftedMousePosition.y + ( YPOS * 2 ) - XPOS + ( ( TILEX - 34 ) / 2 * 32 ) );

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

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    int m = getMapIndexFromMousePosition( mousePosition, true );

    if ( mapIndexIsValid( m ) && userClickedOnMap( mousePosition ) )
    {
      commands_.emplace_back( std::make_shared< MenAmongGods::MoveCommand >( map_.getX( m ), map_.getY( m ) ) );
    }
  }

  // User attempts to select a character
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left &&
       sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LAlt ) )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    int m = getMapIndexFromMousePosition( mousePosition, true );

    int characterId = map_.getCharacterId( m );
    if ( characterId != 0 )
    {
      if ( playerData_.getSelectedCharacter() == characterId )
      {
        playerData_.setSelectedCharacter( 0 );
      }
      else
      {
        playerData_.setSelectedCharacter( characterId );
      }
    }
    return;
  }

  // User attempts to look at a character
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Right &&
       sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LControl ) )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    int m = getMapIndexFromMousePosition( mousePosition, true );

    int characterId = map_.getCharacterId( m );
    if ( characterId != 0 )
    {
      commands_.push_back( std::make_shared< MenAmongGods::LookCommand >( characterId ) );
    }
    return;
  }

  // User faces his/her character a specific direction via a right mouse button click
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Right )
  {
    // Attempting to port similar logic from inter.c::mouse_mapbox()
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    int m = getMapIndexFromMousePosition( mousePosition, false );

    if ( mapIndexIsValid( m ) )
    {
      commands_.emplace_back( std::make_shared< MenAmongGods::TurnCommand >( map_.getX( m ), map_.getY( m ) ) );
    }
  }

  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LControl ) && e.type == sf::Event::MouseButtonReleased &&
       e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    int m = getMapIndexFromMousePosition( mousePosition, true );

    // Check if character is present on tile?
    if ( map_.getCharacterId( m ) != 0 )
    {
      commands_.emplace_back( std::make_shared< MenAmongGods::AttackCommand >( map_.getCharacterId( m ) ) );
    }
  }

  // PICKUP or drop items
  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LShift ) && e.type == sf::Event::MouseButtonReleased &&
       e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    int m = getMapIndexFromMousePosition( mousePosition, false );

    cmap      clickedTile = map_.getMap( m );
    const int x           = clickedTile.x;
    const int y           = clickedTile.y;

    if ( playerData_.getCarriedItem() != 0 && ! ( map_.getFlags( m ) & ISITEM ) )
    {
      commands_.emplace_back( std::make_shared< MenAmongGods::DropCommand >( x, y ) );
    }

    if ( map_.getFlags( m ) & ISITEM )
    {
      if ( map_.getFlags( m ) & ISUSABLE )
      {
        commands_.emplace_back( std::make_shared< MenAmongGods::UseCommand >( x, y ) );
      }
      else
      {
        commands_.emplace_back( std::make_shared< MenAmongGods::PickupCommand >( x, y ) );
      }
    }
  }
}

sf::Vector2i MapDisplay::dd_gputtext( int xpos, int ypos, std::string text, int xoff, int yoff )
{
  int rx = static_cast< int >( ( xpos / 2 ) + ( ypos / 2 ) + 32 - ( ( text.length() * 5 ) / 2 ) + XPOS );
  if ( xpos < 0 && ( xpos & 1 ) )
  {
    rx--;
  }
  if ( ypos < 0 && ( ypos & 1 ) )
  {
    rx--;
  }
  int ry = static_cast< int >( ( xpos / 4 ) - ( ypos / 4 ) + YPOS - 64 );
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

  return sf::Vector2i { rx, ry };
}

void MapDisplay::update()
{
  spritesToDraw_.clear();
  textToDraw_.clear();

  int x {};
  int y {};
  int tmp {};
  int selected_visible {};
  int alpha {};
  int alphastr {};
  int hightlight {};
  int selected_char = playerData_.getSelectedCharacter();

  int xoff       = -map_.getObjectXOffset( ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX ) - 176; //-176;
  int yoff       = -map_.getObjectYOffset( ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX );       //-176;
  int plr_sprite = map_.getObject2( ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX );

  playerData_.setPlayerSprite( plr_sprite );

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
      if ( map_.getFlags( m ) & INVIS )
      {
        tmp |= 64;
      }
      if ( map_.getFlags( m ) & INFRARED )
      {
        tmp |= 256;
      }
      if ( map_.getFlags( m ) & UWATER )
      {
        tmp |= 512;
      }

      // Most of the floor tiles are 32x32 images
      // The tile itself is on the lower portion of the image
      // 32 px wide and 22px tall approximately
      // xs / ys are the x and y size in tiles (width / 32), and height / 32 respectively

      // What is the difference between ba_sprite and back? Can I always use ba_sprite?
      // by using ba_sprite instead; we fixed the intermittent "blank" sprite issue
      copysprite( map_.getBackground( m ), map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff );

      if ( playerData_.getGotoPosition().x == map_.getX( m ) && playerData_.getGotoPosition().y == map_.getY( m ) )
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

      if ( map_.getFlags( x + y * MAPX ) & INVIS )
      {
        tmp = 128;
      }
      else
      {
        tmp = 0;
      }

      if ( map_.getFlags( m ) & INFRARED )
      {
        tmp |= 256;
      }
      if ( map_.getFlags( m ) & UWATER )
      {
        tmp |= 512;
      }

      // object
      if ( playerData_.areWallsHidden() == 0 || ( map_.getFlags( m ) & ISITEM ) || autohide( x, y ) )
      {
        int tmp2 {};

        if ( map_.getObject1( m ) > 16335 && map_.getObject1( m ) < 16422 && map_.getObject1( m ) != 16357 &&
             map_.getObject1( m ) != 16365 && map_.getObject1( m ) != 16373 && map_.getObject1( m ) != 16381 &&
             map_.getObject1( m ) != 16357 && map_.getObject1( m ) != 16389 && map_.getObject1( m ) != 16397 &&
             map_.getObject1( m ) != 16405 && map_.getObject1( m ) != 16413 && map_.getObject1( m ) != 16421 &&
             ! facing( x, y, playerData_.getPlayerDirection() ) && ! autohide( x, y ) && playerData_.areWallsHidden() )
        { // mine hack
          if ( map_.getObject1( m ) < 16358 )
          {
            tmp2 = 457;
          }
          else if ( map_.getObject1( m ) < 16366 )
          {
            tmp2 = 456;
          }
          else if ( map_.getObject1( m ) < 16374 )
          {
            tmp2 = 455;
          }
          else if ( map_.getObject1( m ) < 16382 )
          {
            tmp2 = 466;
          }
          else if ( map_.getObject1( m ) < 16390 )
          {
            tmp2 = 459;
          }
          else if ( map_.getObject1( m ) < 16398 )
          {
            tmp2 = 458;
          }
          else if ( map_.getObject1( m ) < 16398 )
          {
            tmp2 = 449;
          }
          else if ( map_.getObject1( m ) < 16406 )
          {
            tmp2 = 468;
          }
          else
          {
            tmp2 = 467;
          }

          if ( hightlight == HL_MAP && tileType_ == 1 && tileX_ == x && tileY_ == y )
          {
            copysprite( tmp2, map_.getLight( m ) | 16 | tmp, x * 32, y * 32, xoff, yoff );
          }
          else
          {
            copysprite( tmp2, map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff );
          }
        }
        else
        {
          if ( hightlight == HL_MAP && tileType_ == 1 && tileX_ == x && tileY_ == y )
          {
            copysprite( map_.getObject1( m ), map_.getLight( m ) | 16 | tmp, x * 32, y * 32, xoff, yoff );
          }
          else
          {
            copysprite( map_.getObject1( m ), map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff );
          }
        }
      }
      else if ( map_.getObject1( m ) )
      {
        copysprite( map_.getObject1( m ) + 1, map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff );
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

      if ( map_.getCharacterId( m ) == selected_char )
      {
        tmp |= 32;
        selected_visible = 1;
      }

      if ( map_.getFlags( m ) & INVIS )
      {
        tmp |= 64;
      }
      if ( map_.getFlags( m ) & STONED )
      {
        tmp |= 128;
      }
      if ( map_.getFlags( m ) & INFRARED )
      {
        tmp |= 256;
      }
      if ( map_.getFlags( m ) & UWATER )
      {
        tmp |= 512;
      }

      if ( map_.getObject2( m ) != 0 )
      {
        bool isSelected = map_.getCharacterId( m ) == playerData_.getSelectedCharacter();
        copysprite( map_.getObject2( m ), map_.getLight( m ) | tmp, x * 32, y * 32, xoff + map_.getObjectXOffset( m ),
                    yoff + map_.getObjectYOffset( m ), isSelected );
      }

      if ( playerData_.getAttackTarget() != 0 && playerData_.getAttackTarget() == map_.getCharacterId( m ) )
      {
        copysprite( 34, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ) );
      }

      if ( playerData_.getPlayerAction() == DR_GIVE && playerData_.getFirstTarget() == map_.getCharacterCrc( m ) )
      {
        copysprite( 45, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ) );
      }

      if ( ( playerData_.clientShouldShowNames() | playerData_.clientShouldShowPercentHealth() ) && map_.getCharacterId( m ) )
      {
        playerData_.set_look_proz( map_.getCharacterId( m ), map_.getCharacterCrc( m ), map_.getCharacterPercentHealth( m ) );

        std::string stringToDraw = playerData_.lookup( map_.getCharacterId( m ), map_.getCharacterCrc( m ) );
        textToDraw_.emplace_back( stringToDraw, font_, FONT_SIZE );

        sf::Vector2i textPosition =
            dd_gputtext( x * 32, y * 32, stringToDraw, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ) );

        auto& lastText = *( textToDraw_.end() - 1 );

        lastText.setPosition( sf::Vector2f { static_cast< float >( textPosition.x ), static_cast< float >( textPosition.y ) } );
        lastText.setOutlineColor( sf::Color::Black );
        lastText.setOutlineThickness( 1.0f );
        lastText.setFillColor( MenAmongGods::MsgYellow );
      }

      if ( playerData_.getPlayerAction() == DR_DROP && playerData_.getFirstTarget() == map_.getX( m ) &&
           playerData_.getSecondTarget() == map_.getY( m ) )
      {
        copysprite( 32, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( playerData_.getPlayerAction() == DR_PICKUP && playerData_.getFirstTarget() == map_.getX( m ) &&
           playerData_.getSecondTarget() == map_.getY( m ) )
      {
        copysprite( 33, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( playerData_.getPlayerAction() == DR_USE && playerData_.getFirstTarget() == map_.getX( m ) &&
           playerData_.getSecondTarget() == map_.getY( m ) )
      {
        copysprite( 45, 0, x * 32, y * 32, xoff, yoff );
      }

      // effects
      if ( map_.getFlags2( m ) & MF_MOVEBLOCK )
      {
        copysprite( 55, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_SIGHTBLOCK )
      {
        copysprite( 84, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_INDOORS )
      {
        copysprite( 56, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_UWATER )
      {
        copysprite( 75, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_NOMONST )
      {
        copysprite( 59, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_BANK )
      {
        copysprite( 60, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_TAVERN )
      {
        copysprite( 61, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_NOMAGIC )
      {
        copysprite( 62, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_DEATHTRAP )
      {
        copysprite( 73, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_NOLAG )
      {
        copysprite( 57, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_ARENA )
      {
        copysprite( 76, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & MF_NOEXPIRE )
      {
        copysprite( 82, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_.getFlags2( m ) & 0x80000000 )
      {
        copysprite( 72, 0, x * 32, y * 32, xoff, yoff );
      }

      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == INJURED )
      {
        copysprite( 1079, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ) );
      }
      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 ) )
      {
        copysprite( 1080, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ) );
      }
      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED2 ) )
      {
        copysprite( 1081, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ) );
      }
      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 | INJURED2 ) )
      {
        copysprite( 1082, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ) );
      }

      if ( map_.getFlags( m ) & DEATH )
      {
        if ( map_.getObject2( m ) )
        {
          copysprite( 280 + ( ( map_.getFlags( m ) & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ),
                      yoff + map_.getObjectYOffset( m ) );
        }
        else
        {
          copysprite( 280 + ( ( map_.getFlags( m ) & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff, yoff );
        }
      }
      if ( map_.getFlags( m ) & TOMB )
      {
        copysprite( 240 + ( ( map_.getFlags( m ) & TOMB ) >> 12 ) - 1, map_.getLight( m ), x * 32, y * 32, xoff, yoff );
      }

      alpha    = 0;
      alphastr = 0;

      if ( map_.getFlags( m ) & EMAGIC )
      {
        alpha |= 1;
        alphastr = std::max( ( unsigned ) alphastr, ( ( map_.getFlags( m ) & EMAGIC ) >> 22 ) );
      }

      if ( map_.getFlags( m ) & GMAGIC )
      {
        alpha |= 2;
        alphastr = std::max( ( unsigned ) alphastr, ( ( map_.getFlags( m ) & GMAGIC ) >> 25 ) );
      }

      if ( map_.getFlags( m ) & CMAGIC )
      {
        alpha |= 4;
        alphastr = std::max( ( unsigned ) alphastr, ( ( map_.getFlags( m ) & CMAGIC ) >> 28 ) );
      }

      if ( alpha )
      {
        // dd_alphaeffect_magic( alpha, alphastr, x * 32, y * 32, xoff + map_.getObjectXOffset(m), yoff + map_.getObjectYOffset(m)
        // );
      }
    }
  }

  if ( ! selected_visible )
  {
    playerData_.setSelectedCharacter( 0 );
  }

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
        map_.setMap( x + y * MAPX, tmpMap );
      }
    }
  }

  mapFile.close();
}

void MapDisplay::copysprite( int nr, int effect, int xpos, int ypos, int xoff, int yoff, bool isCharacterSelected )
{
  if ( nr == 0 )
  {
    return;
  }

  spritesToDraw_.push_back( cache_.getSprite( nr ) );
  sf::Sprite& newSprite = *( spritesToDraw_.end() - 1 );

  // xs / ys are the x and y size in tiles (width / 32), and height / 32 respectively
  unsigned char xs = newSprite.getTexture()->getSize().x / 32;
  unsigned char ys = newSprite.getTexture()->getSize().y / 32;

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
    for ( unsigned int x = 0; x < 1; x++ )
    {
      newSprite.setPosition( sf::Vector2f { static_cast< float >( rx + x * 32 ), static_cast< float >( ry + y * 32 ) } );
      ( void ) effect;

      if ( isCharacterSelected )
      {
        newSprite.setColor( sf::Color::Green );
      }
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
        oa << map_.getMap( x + y * MAPX );
      }
    }
  }
  mapFile.close();
}

} // namespace MenAmongGods