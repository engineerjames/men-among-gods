#include "Map.h"

#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>

#include "../ConstantIdentifiers.h"

namespace MenAmongGods
{

Map::Map()
    : map_( std::make_unique< cmap[] >( MAPX * MAPY ) )
{
}

void Map::draw( sf::RenderTarget&, sf::RenderStates ) const
{
  // target.draw()
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
}

void Map::update()
{
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

  int mapx = map_[ ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX ].x;
  int mapy = map_[ ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX ].y;

  ( void ) xoff;
  ( void ) yoff;
  ( void ) plr_sprite;
  ( void ) mapx;
  ( void ) mapy;
  ( void ) selected_visible;

  for ( y = TILEY - 1; y >= 0; y-- )
  {
    for ( x = 0; x < TILEX; x++ )
    {
      // background
      int m = x + y * MAPX;

      if ( hightlight == HL_MAP && tile_type == 0 && tile_x == x && tile_y == y )
        tmp = 16;
      else
        tmp = 0;
      if ( map_[ m ].flags & INVIS )
        tmp |= 64;
      if ( map_[ m ].flags & INFRARED )
        tmp |= 256;
      if ( map_[ m ].flags & UWATER )
        tmp |= 512;

      // display_floortile( map_[ m ].back, map_[ m ].light | tmp, x * 32, y * 32, xoff, yoff, map_[ x + y * MAPX ].x, map_[ x + y * MAPX
      // ].y );

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
            // copysprite( tmp2, map_[ m ].light | 16 | tmp, x * 32, y * 32, xoff, yoff );
          }
          else
          {
            // copysprite( tmp2, map_[ m ].light | tmp, x * 32, y * 32, xoff, yoff );
          }
        }
        else
        {
          if ( hightlight == HL_MAP && tile_type == 1 && tile_x == x && tile_y == y )
          {
            // copysprite( map_[ m ].obj1, map_[ m ].light | 16 | tmp, x * 32, y * 32, xoff, yoff );
          }
          else
          {
            // copysprite( map_[ m ].obj1, map_[ m ].light | tmp, x * 32, y * 32, xoff, yoff );
          }
        }
      }
      else if ( map_[ m ].obj1 )
      {
        // copysprite( map_[ m ].obj1 + 1, map_[ m ].light | tmp, x * 32, y * 32, xoff, yoff );
      }

      if ( map_[ m ].obj1 && map_[ m ].x < 1024 && map_[ m ].y < 1024 )
      {
        // xmap_[ map_[ m ].y + map_[ m ].x * 1024 ] = ( unsigned short ) get_avgcol( map_[ m ].obj1 );
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

      // copysprite( map_[ m ].obj2, map_[ m ].light | tmp, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );

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
        // copysprite( 55, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_SIGHTBLOCK )
      {
        // copysprite( 84, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_INDOORS )
      {
        // copysprite( 56, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_UWATER )
      {
        // copysprite( 75, 0, x * 32, y * 32, xoff, yoff );
      }
      //				if (map_[m].flags2&MF_NOFIGHT) copysprite(58,0,x*32,y*32,xoff,yoff);
      if ( map_[ m ].flags2 & MF_NOMONST )
      {
        // copysprite( 59, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_BANK )
      {
        // copysprite( 60, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_TAVERN )
      {
        // copysprite( 61, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_NOMAGIC )
      {
        // copysprite( 62, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_DEATHTRAP )
      {
        // copysprite( 73, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_NOLAG )
      {
        // copysprite( 57, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & MF_ARENA )
      {
        // copysprite( 76, 0, x * 32, y * 32, xoff, yoff );
      }
      //				if (map_[m].flags2&MF_TELEPORT2) copysprite(77,0,x*32,y*32,xoff,yoff);
      if ( map_[ m ].flags2 & MF_NOEXPIRE )
      {
        // copysprite( 82, 0, x * 32, y * 32, xoff, yoff );
      }
      if ( map_[ m ].flags2 & 0x80000000 )
      {
        // copysprite( 72, 0, x * 32, y * 32, xoff, yoff );
      }

      if ( ( map_[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == INJURED )
      {
        // copysprite( 1079, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      }
      if ( ( map_[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 ) )
      {
        // copysprite( 1080, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      }
      if ( ( map_[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED2 ) )
      {
        // copysprite( 1081, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      }
      if ( ( map_[ m ].flags & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 | INJURED2 ) )
      {
        // copysprite( 1082, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff, yoff + map_[ m ].obj_yoff );
      }

      if ( map_[ m ].flags & DEATH )
      {
        if ( map_[ m ].obj2 )
        {
          //   copysprite( 280 + ( ( map_[ m ].flags & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff + map_[ m ].obj_xoff,
          //               yoff + map_[ m ].obj_yoff );
        }
        else
        {
          // copysprite( 280 + ( ( map_[ m ].flags & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff, yoff );
        }
      }
      if ( map_[ m ].flags & TOMB )
      {
        // copysprite( 240 + ( ( map_[ m ].flags & TOMB ) >> 12 ) - 1, map_[ m ].light, x * 32, y * 32, xoff, yoff );
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

} // namespace MenAmongGods