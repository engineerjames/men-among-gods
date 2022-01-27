#include "Map.h"

#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>

#include "../ConstantIdentifiers.h"
#include "GraphicsCache.h"

namespace MenAmongGods
{

Map::Map( const GraphicsCache& cache )
    : map_( std::make_unique< cmap[] >( MAPX * MAPY ) )
    , cache_( cache )
    , spritesToDraw_()
{
}

void Map::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( const auto& tile : spritesToDraw_ )
  {
    target.draw( tile, states );
  }
}

void Map::loadFromFile( std::string filePath )
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
        map_[ x + y * MAPX ] = tmpMap;
      }
    }
  }
  // 497 to 530
  mapFile.close();

  // Need to perform the regular "engine tick" here:
  for ( unsigned int n = 0; n < TILEX * TILEY; n++ )
  {
    map_[ n ].back     = 0;
    map_[ n ].obj1     = 0;
    map_[ n ].obj2     = 0;
    map_[ n ].ovl_xoff = 0;
    map_[ n ].ovl_yoff = 0;
  }

  for ( unsigned int n = 0; n < TILEX * TILEY; n++ )
  {

    map_[ n ].back = map_[ n ].ba_sprite;

    // TODO: Fix the eng_item and eng_char retrieval

    // item
    if ( map_[ n ].it_sprite )
    {
      //   int tmp        = eng_item( n );
      map_[ n ].obj1 = map_[ n ].it_sprite;
    }

    // character
    if ( map_[ n ].ch_sprite )
    {
      //   int tmp        = eng_char( n );
      //   map_[ n ].obj2 = tmp;
      map_[ n ].obj2 = map_[ n ].ch_sprite;
    }
  }

  this->update();
}

void Map::update()
{
  spritesToDraw_.clear();

  int x {};
  int y {};
  int tmp {};
  int selected_visible {};
  int alpha {};
  int alphastr {};
  int hightlight {};
  int tile_type {};
  int tile_x {}; // user goto?
  int tile_y {}; // user goto value?
  int selected_char {};

  int xoff       = -map_[ ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX ].obj_xoff - 176; //-176;
  int yoff       = -map_[ ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX ].obj_yoff;       //-176;
  int plr_sprite = map_[ ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX ].obj2;

  ( void ) xoff;
  ( void ) yoff;
  ( void ) plr_sprite;
  ( void ) selected_visible;

  for ( y = TILEY - 1; y >= 0; y-- )
  {
    for ( x = 0; x < TILEX; x++ )
    {
      // background
      int m = x + y * MAPX;

      if ( hightlight == HL_MAP && tile_type == 0 && tile_x == x && tile_y == y )
      {
        tmp = 16;
      }
      else
      {
        tmp = 0;
      }
      if ( map_[ m ].flags & INVIS )
      {
        tmp |= 64;
      }
      if ( map_[ m ].flags & INFRARED )
      {
        tmp |= 256;
      }
      if ( map_[ m ].flags & UWATER )
      {
        tmp |= 512;
      }

      // Most of the floor tiles are 32x32 images
      // The tile itself is on the lower portion of the image
      // 32 px wide and 22px tall approximately
      // xs / ys are the x and y size in tiles (width / 32), and height / 32 respectively

      // What is the difference between ba_sprite and back? Can I always use ba_sprite?
      // by using ba_sprite instead; we fixed the intermittent "blank" sprite issue
      copysprite( map_[ m ].back, map_[ m ].light | tmp, x * 32, y * 32, xoff, yoff );

      //   if ( map_[ m ].x < 1024 && map_[ m ].y < 1024 && ! ( map_[ m ].flags & INVIS ) )
      //   {
      //     if ( ! xmap_[ map_[ m ].y + map_[ m ].x * 1024 ] || xmap_[ map_[ m ].y + map_[ m ].x * 1024 ] == 0xffff )

      //       xmap_[ map_[ m ].y + map_[ m ].x * 1024 ] = ( unsigned short ) get_avgcol( map_[ m ].back );
      //   }

      // TODO: We do need this part--highlight the tile that the user has selected
      //   if ( pl.goto_x == map_[ m ].x && pl.goto_y == map_[ m ].y )
      //   {
      //     // copysprite( 31, 0, x * 32, y * 32, xoff, yoff );
      //   }
    }
  }

  for ( y = TILEY - 1; y >= 0; y-- )
  {
    for ( x = 0; x < TILEX; x++ )
    {
      int m = x + y * MAPX;

      if ( map_[ x + y * MAPX ].flags & INVIS )
      {
        continue;
      } // tmp=128;
      else
      {
        tmp = 0;
      }

      if ( map_[ m ].flags & INFRARED )
      {
        tmp |= 256;
      }
      if ( map_[ m ].flags & UWATER )
      {
        tmp |= 512;
      }

      // object
      if /* ( pdata.hide == 0 ||*/ ( map_[ m ].flags & ISITEM ) /* || autohide( x, y ) ) */
      {
        int tmp2 {};
        ( void ) tmp2;

        if ( map_[ m ].obj1 > 16335 && map_[ m ].obj1 < 16422 && map_[ m ].obj1 != 16357 && map_[ m ].obj1 != 16365 &&
             map_[ m ].obj1 != 16373 && map_[ m ].obj1 != 16381 && map_[ m ].obj1 != 16357 && map_[ m ].obj1 != 16389 &&
             map_[ m ].obj1 != 16397 && map_[ m ].obj1 != 16405 && map_[ m ].obj1 != 16413 && map_[ m ].obj1 != 16421 ) /* &&
             ! facing( x, y, pl.dir ) && ! autohide( x, y ) && pdata.hide ) */
        {                                                                                                               // mine hack
          if ( map_[ m ].obj1 < 16358 )
          {
            tmp2 = 457;
          }
          else if ( map_[ m ].obj1 < 16366 )
          {
            tmp2 = 456;
          }
          else if ( map_[ m ].obj1 < 16374 )
          {
            tmp2 = 455;
          }
          else if ( map_[ m ].obj1 < 16382 )
          {
            tmp2 = 466;
          }
          else if ( map_[ m ].obj1 < 16390 )
          {
            tmp2 = 459;
          }
          else if ( map_[ m ].obj1 < 16398 )
          {
            tmp2 = 458;
          }
          else if ( map_[ m ].obj1 < 16398 )
          {
            tmp2 = 449;
          }
          else if ( map_[ m ].obj1 < 16406 )
          {
            tmp2 = 468;
          }
          else
          {
            tmp2 = 467;
          }

          if ( hightlight == HL_MAP && tile_type == 1 && tile_x == x && tile_y == y )
          {
            copysprite( tmp2, map_[ m ].light | 16 | tmp, x * 32, y * 32, xoff, yoff );
          }
          else
          {
            copysprite( tmp2, map_[ m ].light | tmp, x * 32, y * 32, xoff, yoff );
          }
        }
        else
        {
          if ( hightlight == HL_MAP && tile_type == 1 && tile_x == x && tile_y == y )
          {
            copysprite( map_[ m ].obj1, map_[ m ].light | 16 | tmp, x * 32, y * 32, xoff, yoff );
          }
          else
          {
            copysprite( map_[ m ].obj1, map_[ m ].light | tmp, x * 32, y * 32, xoff, yoff );
          }
        }
      }
      else if ( map_[ m ].obj1 )
      {
        copysprite( map_[ m ].obj1 + 1, map_[ m ].light | tmp, x * 32, y * 32, xoff, yoff );
      }

      // character
      if ( tile_type == 2 && tile_x == x && tile_y == y )
      {
        tmp = 16;
      }
      else
      {
        tmp = 0;
      }

      if ( map_[ m ].ch_nr == selected_char )
      {
        tmp |= 32;
        selected_visible = 1;
      }

      if ( map_[ m ].flags & INVIS )
      {
        tmp |= 64;
      }
      if ( map_[ m ].flags & STONED )
      {
        tmp |= 128;
      }
      if ( map_[ m ].flags & INFRARED )
      {
        tmp |= 256;
      }
      if ( map_[ m ].flags & UWATER )
      {
        tmp |= 512;
      }

      //   if ( do_shadow )
      //     {
      //     // dd_shadow( map_[ m ].obj2, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff + 4 );
      //     }
      if ( map_[ m ].obj2 != 0 )
      {
        copysprite( map_[ m ].obj2, map_[ m ].light | tmp, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      }
      //   if ( pl.attack_cn && pl.attack_cn == map_[ m ].ch_nr )
      //   {
      //     copysprite( 34, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      //   }

      //   if ( pl.misc_action == DR_GIVE && pl.misc_target1 == map_[ m ].ch_id )
      //   {
      //     copysprite( 45, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      //   }

      //   if ( ( pdata.show_names | pdata.show_proz ) && map_[ m ].ch_nr )
      //   {
      //     set_look_proz( map_[ m ].ch_nr, map_[ m ].ch_id, map_[ m ].ch_proz );
      //     dd_gputtext( x * 32, y * 32, 1, lookup( map_[ m ].ch_nr, map_[ m ].ch_id ), xoff + map_[ m ].obj_xoff, yoff + map_[ m
      //     ].obj_yoff );
      //   }

      //   if ( pl.misc_action == DR_DROP && pl.misc_target1 == map_[ m ].x && pl.misc_target2 == map_[ m ].y )
      //   {
      //     copysprite( 32, 0, x * 32, y * 32, xoff, yoff );
      //   }
      //   if ( pl.misc_action == DR_PICKUP && pl.misc_target1 == map_[ m ].x && pl.misc_target2 == map_[ m ].y )
      //   {
      //     copysprite( 33, 0, x * 32, y * 32, xoff, yoff );
      //   }
      //   if ( pl.misc_action == DR_USE && pl.misc_target1 == map_[ m ].x && pl.misc_target2 == map_[ m ].y )
      //   {
      //     copysprite( 45, 0, x * 32, y * 32, xoff, yoff );
      //   }

      // effects
      if ( map_[ m ].flags2 & MF_MOVEBLOCK )
      {
        copysprite( 55, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_SIGHTBLOCK )
      {
        copysprite( 84, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_INDOORS )
      {
        copysprite( 56, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_UWATER )
      {
        copysprite( 75, 0, x * 32, y * 32, xoff, yoff );
      }
      //				if (map_[m].flags2&MF_NOFIGHT) copysprite(58,0,x*32,y*32,xoff,yoff);
      if ( map_[ m ].flags2 & MF_NOMONST )
      {
        copysprite( 59, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_BANK )
      {
        copysprite( 60, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_TAVERN )
      {
        copysprite( 61, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_NOMAGIC )
      {
        copysprite( 62, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_DEATHTRAP )
      {
        copysprite( 73, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_NOLAG )
      {
        copysprite( 57, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_ARENA )
      {
        copysprite( 76, 0, x * 32, y * 32, xoff, yoff );
      }
      //				if (map_[m].flags2&MF_TELEPORT2) copysprite(77,0,x*32,y*32,xoff,yoff);
      if ( map_[ m ].flags2 & MF_NOEXPIRE )
      {
        copysprite( 82, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & 0x80000000 )
      {
        copysprite( 72, 0, x * 32, y * 32, xoff, yoff );
      }

      if ( ( map_[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == INJURED )
      {
        copysprite( 1079, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      }
      if ( ( map_[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 ) )
      {
        copysprite( 1080, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      }
      if ( ( map_[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED2 ) )
      {
        copysprite( 1081, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      }
      if ( ( map_[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 | INJURED2 ) )
      {
        copysprite( 1082, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      }

      if ( map_[ m ].flags & DEATH )
      {
        if ( map_[ m ].obj2 )
        {
          copysprite( 280 + ( ( map_[ m ].flags & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff,
                      yoff + map_[ m ].obj_yoff );
        }
        else
        {
          copysprite( 280 + ( ( map_[ m ].flags & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff, yoff );
        }
      }
      if ( map_[ m ].flags & TOMB )
      {
        copysprite( 240 + ( ( map_[ m ].flags & TOMB ) >> 12 ) - 1, map_[ m ].light, x * 32, y * 32, xoff, yoff );
      }

      alpha    = 0;
      alphastr = 0;

      if ( map_[ m ].flags & EMAGIC )
      {
        alpha |= 1;
        alphastr = std::max( ( unsigned ) alphastr, ( ( map_[ m ].flags & EMAGIC ) >> 22 ) );
      }

      if ( map_[ m ].flags & GMAGIC )
      {
        alpha |= 2;
        alphastr = std::max( ( unsigned ) alphastr, ( ( map_[ m ].flags & GMAGIC ) >> 25 ) );
      }

      if ( map_[ m ].flags & CMAGIC )
      {
        alpha |= 4;
        alphastr = std::max( ( unsigned ) alphastr, ( ( map_[ m ].flags & CMAGIC ) >> 28 ) );
      }
      if ( alpha )
      {
        // dd_alphaeffect_magic( alpha, alphastr, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
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
}

void Map::copysprite( int nr, int effect, int xpos, int ypos, int xoff, int yoff )
{
  if ( nr == 0 )
  {
    return;
  }

  ( void ) effect;

  // xs / ys are the x and y size in tiles (width / 32), and height / 32 respectively
  const sf::Image* imageDetails = cache_.getImageDetails( nr );

  unsigned int xs = imageDetails->getSize().x / 32;
  unsigned int ys = imageDetails->getSize().y / 32;

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

  // std::cerr << rx << ", " << ry << std::endl;

  for ( unsigned int y = 0; y < 1; y++ )
  {
    for ( unsigned int x = 0; x < 1; x++ ) // TODO: Change this back to 1/1 instead of xs/ys in order to "fix" rendering issue
    {
      // n = gettile( nr, effect, x, y, xs );

      // This is where we have all the data we need now to copy sprites out to a.. draw list?
      spritesToDraw_.push_back( cache_.getSprite( nr ) );
      sf::Sprite& newSprite = *( spritesToDraw_.end() - 1 );
      newSprite.setPosition( sf::Vector2f { static_cast< float >( rx + x * 32 ), static_cast< float >( ry + y * 32 ) } );
    }
  }
  //   if ( sprtab[ nr ].alpha )
  //     display_alpha( sprtab[ nr ].alpha, sprtab[ nr ].alphacnt, rx, ry, effect );
}

} // namespace MenAmongGods