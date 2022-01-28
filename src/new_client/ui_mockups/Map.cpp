#include "Map.h"

#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>

#include "../ConstantIdentifiers.h"
#include "../TickBuffer.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"

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

const unsigned char speedtab[ 20 ][ 20 ] = {
    //  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 20
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 19
    { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 }, // 18
    { 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 }, // 17
    { 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1 }, // 16
    { 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1 }, // 15
    { 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1 }, // 14
    { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 }, // 13
    { 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 }, // 12
    { 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1 }, // 11
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // 10
    { 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0 }, // 9
    { 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0 }, // 8
    { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 }, // 7
    { 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 }, // 6
    { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 }, // 5
    { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 }, // 4
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }, // 3
    { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }, // 2
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }  // 1
};

// const unsigned char speedsteptab[ 20 ][ 20 ] = {
//     //  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
//     { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }, // 20
//     { 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }, // 19
//     { 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4 }, // 18
//     { 4, 4, 4, 2, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4 }, // 17
//     { 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4 }, // 16
//     { 4, 4, 2, 4, 4, 4, 2, 4, 4, 4, 2, 4, 4, 4, 2, 4, 4, 4, 2, 4 }, // 15
//     { 4, 2, 4, 4, 2, 4, 4, 4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 2, 4, 4 }, // 14
//     { 4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 2 }, // 13
//     { 2, 4, 4, 2, 4, 4, 2, 4, 2, 4, 4, 2, 4, 4, 2, 4, 2, 4, 2, 4 }, // 12
//     { 2, 4, 2, 4, 2, 4, 2, 4, 4, 2, 4, 2, 4, 2, 4, 2, 4, 4, 2, 4 }, // 11
//     { 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2 }, // 10
//     { 4, 2, 4, 2, 4, 2, 4, 1, 3, 4, 2, 4, 2, 4, 2, 4, 1, 2, 4, 2 }, // 9
//     { 4, 1, 2, 4, 1, 3, 4, 2, 4, 1, 2, 4, 1, 3, 4, 2, 4, 2, 4, 2 }, // 8
//     { 2, 4, 1, 3, 4, 1, 3, 4, 1, 3, 4, 1, 3, 4, 1, 3, 4, 1, 3, 4 }, // 7
//     { 3, 4, 1, 3, 4, 1, 2, 3, 4, 1, 3, 4, 1, 3, 4, 1, 3, 4, 1, 2 }, // 6
//     { 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1 }, // 5
//     { 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1 }, // 4
//     { 2, 3, 4, 4, 1, 1, 2, 2, 3, 4, 1, 1, 2, 2, 3, 4, 4, 1, 1, 2 }, // 3
//     { 2, 3, 3, 4, 4, 4, 1, 1, 1, 2, 2, 2, 3, 3, 4, 1, 1, 1, 2, 2 }, // 2
//     { 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 }  // 1
// };

} // namespace

namespace MenAmongGods
{

Map::Map( const GraphicsCache& cache, const GraphicsIndex& index, const TickBuffer& tickBuffer )
    : sf::Drawable()
    , MenAmongGods::Component()
    , map_( std::make_unique< cmap[] >( MAPX * MAPY ) )
    , cache_( cache )
    , index_( index )
    , tickBuffer_( tickBuffer )
    , spritesToDraw_()
    , ticker_()
    , needsToUpdate_( true )
    , ctick_( 0 )
{
}

int Map::speedo( int n )
{
  return speedtab[ map_[ n ].ch_speed ][ 0 ]; // 0 -> ctick
}

void Map::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( const auto& tile : spritesToDraw_ )
  {
    target.draw( tile, states );
  }
}

void Map::finalize()
{
  needsToUpdate_ = true;
}

void Map::onUserInput( const sf::Event& )
{
  // Do nothing for now
}

void Map::update()
{
  // TODO: Handle mouse events here? Maybe we should have a user input component instead...

  // Perform once-per-frame updates
  if ( needsToUpdate_ )
  {
    ticker_++; // Should this be at the end?
    needsToUpdate_ = false;

    ctick_ = tickBuffer_.getCTick();

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

      // item
      if ( map_[ n ].it_sprite != 0 )
      {
        map_[ n ].obj1 = interpolateItemSprite( n );
      }

      // character
      if ( map_[ n ].ch_sprite != 0 )
      {
        map_[ n ].obj2 = interpolateCharacterSprite( n );
      }
    }

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
        if /* ( pdata.hide == 0 ||*/ ( ( map_[ m ].flags & ISITEM ) || autohide( x, y ) )
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

  mapFile.close();
}

int Map::speedstep( int n, int d, int s, int update )
{
  int hard_step {};
  int soft_step {};
  int total_step {};
  int speed {};
  int dist {};
  int z {};
  int m {};

  speed     = map_[ n ].ch_speed;
  hard_step = map_[ n ].ch_status - d;

  if ( ! update )
  {
    return 32 * hard_step / s;
  }

  z         = ctick_;
  soft_step = 0;
  m         = hard_step;

  while ( m )
  {
    z--;
    if ( z < 0 )
    {
      z = 19;
    }
    soft_step++;
    if ( speedtab[ speed ][ z ] )
    {
      m--;
    }
  }
  while ( 1 )
  {
    z--;
    if ( z < 0 )
    {
      z = 19;
    }
    if ( speedtab[ speed ][ z ] )
    {
      break;
    }
    soft_step++;
  }

  z          = ctick_;
  total_step = soft_step;
  m          = s - hard_step;

  while ( 1 )
  {
    if ( speedtab[ speed ][ z ] )
    {
      m--;
    }
    if ( m < 1 )
    {
      break;
    }
    z++;
    if ( z > 19 )
    {
      z = 0;
    }
    total_step++;
  }
  dist = 32 * ( soft_step ) / ( total_step + 1 );

  return dist;
}
//  0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10
static int stattab[] = { 0, 1, 1, 6, 6, 2, 3, 4, 5, 7, 4 };

#define do_idle( ani, sprite ) ( sprite == 22480 ? ani : 0 )

// eng_char
int Map::interpolateCharacterSprite( int mapIndex )
{
  int tmp, update = 1;

  if ( map_[ mapIndex ].flags & STUNNED )
  {
    update = 0;
  }

  switch ( map_[ mapIndex ].ch_status )
  {
  // idle up
  case 0:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    map_[ mapIndex ].idle_ani++;
    if ( map_[ mapIndex ].idle_ani > 7 )
    {
      map_[ mapIndex ].idle_ani = 0;
    }
    return map_[ mapIndex ].ch_sprite + 0 + do_idle( map_[ mapIndex ].idle_ani, map_[ mapIndex ].ch_sprite );
    // idle down
  case 1:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].idle_ani++;
      if ( map_[ mapIndex ].idle_ani > 7 )
      {
        map_[ mapIndex ].idle_ani = 0;
      }
    }
    return map_[ mapIndex ].ch_sprite + 8 + do_idle( map_[ mapIndex ].idle_ani, map_[ mapIndex ].ch_sprite );
    // idle left
  case 2:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].idle_ani++;
      if ( map_[ mapIndex ].idle_ani > 7 )
      {
        map_[ mapIndex ].idle_ani = 0;
      }
    }
    return map_[ mapIndex ].ch_sprite + 16 + do_idle( map_[ mapIndex ].idle_ani, map_[ mapIndex ].ch_sprite );
    // idle right
  case 3:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].idle_ani++;
      if ( map_[ mapIndex ].idle_ani > 7 )
      {
        map_[ mapIndex ].idle_ani = 0;
      }
    }
    return map_[ mapIndex ].ch_sprite + 24 + do_idle( map_[ mapIndex ].idle_ani, map_[ mapIndex ].ch_sprite );

    // idle left-up
  case 4:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].idle_ani++;
      if ( map_[ mapIndex ].idle_ani > 7 )
      {
        map_[ mapIndex ].idle_ani = 0;
      }
    }
    return map_[ mapIndex ].ch_sprite + 32 + do_idle( map_[ mapIndex ].idle_ani, map_[ mapIndex ].ch_sprite );
    // idle left-down
  case 5:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].idle_ani++;
      if ( map_[ mapIndex ].idle_ani > 7 )
      {
        map_[ mapIndex ].idle_ani = 0;
      }
    }
    return map_[ mapIndex ].ch_sprite + 40 + do_idle( map_[ mapIndex ].idle_ani, map_[ mapIndex ].ch_sprite );
    // idle right-up
  case 6:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].idle_ani++;
      if ( map_[ mapIndex ].idle_ani > 7 )
      {
        map_[ mapIndex ].idle_ani = 0;
      }
    }
    return map_[ mapIndex ].ch_sprite + 48 + do_idle( map_[ mapIndex ].idle_ani, map_[ mapIndex ].ch_sprite );
    // idle right-down
  case 7:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].idle_ani++;
      if ( map_[ mapIndex ].idle_ani > 7 )
      {
        map_[ mapIndex ].idle_ani = 0;
      }
    }
    return map_[ mapIndex ].ch_sprite + 56 + do_idle( map_[ mapIndex ].idle_ani, map_[ mapIndex ].ch_sprite );

    // walk up
  case 16:
  case 17:
  case 18:
  case 19:
  case 20:
  case 21:
  case 22:
    map_[ mapIndex ].obj_xoff = -speedstep( mapIndex, 16, 8, update ) / 2;
    map_[ mapIndex ].obj_yoff = speedstep( mapIndex, 16, 8, update ) / 4;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 16 ) + 64;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 23:
    map_[ mapIndex ].obj_xoff = -speedstep( mapIndex, 16, 8, update ) / 2;
    map_[ mapIndex ].obj_yoff = speedstep( mapIndex, 16, 8, update ) / 4;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 16 ) + 64;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 16;
    }
    return tmp;

    // walk down
  case 24:
  case 25:
  case 26:
  case 27:
  case 28:
  case 29:
  case 30:
    map_[ mapIndex ].obj_xoff = speedstep( mapIndex, 24, 8, update ) / 2;
    map_[ mapIndex ].obj_yoff = -speedstep( mapIndex, 24, 8, update ) / 4;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 24 ) + 72;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 31:
    map_[ mapIndex ].obj_xoff = speedstep( mapIndex, 24, 8, update ) / 2;
    map_[ mapIndex ].obj_yoff = -speedstep( mapIndex, 24, 8, update ) / 4;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 24 ) + 72;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 24;
    }
    return tmp;

    // walk left
  case 32:
  case 33:
  case 34:
  case 35:
  case 36:
  case 37:
  case 38:
    map_[ mapIndex ].obj_xoff = -speedstep( mapIndex, 32, 8, update ) / 2;
    map_[ mapIndex ].obj_yoff = -speedstep( mapIndex, 32, 8, update ) / 4;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 32 ) + 80;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 39:
    map_[ mapIndex ].obj_xoff = -speedstep( mapIndex, 32, 8, update ) / 2;
    map_[ mapIndex ].obj_yoff = -speedstep( mapIndex, 32, 8, update ) / 4;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 32 ) + 80;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 32;
    }
    return tmp;

    // walk right
  case 40:
  case 41:
  case 42:
  case 43:
  case 44:
  case 45:
  case 46:
    map_[ mapIndex ].obj_xoff = speedstep( mapIndex, 40, 8, update ) / 2;
    map_[ mapIndex ].obj_yoff = speedstep( mapIndex, 40, 8, update ) / 4;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 40 ) + 88;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 47:
    map_[ mapIndex ].obj_xoff = speedstep( mapIndex, 40, 8, update ) / 2;
    map_[ mapIndex ].obj_yoff = speedstep( mapIndex, 40, 8, update ) / 4;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 40 ) + 88;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 40;
    }
    return tmp;

    // left+up
  case 48:
  case 49:
  case 50:
  case 51:
  case 52:
  case 53:
  case 54:
  case 55:
  case 56:
  case 57:
  case 58:
    map_[ mapIndex ].obj_xoff = -speedstep( mapIndex, 48, 12, update );
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 48 ) * 8 / 12 + 96;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 59:
    map_[ mapIndex ].obj_xoff = -speedstep( mapIndex, 48, 12, update );
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 48 ) * 8 / 12 + 96;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 48;
    }
    return tmp;

    // left+down
  case 60:
  case 61:
  case 62:
  case 63:
  case 64:
  case 65:
  case 66:
  case 67:
  case 68:
  case 69:
  case 70:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = -speedstep( mapIndex, 60, 12, update ) / 2;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 60 ) * 8 / 12 + 104;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 71:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = -speedstep( mapIndex, 60, 12, update ) / 2;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 60 ) * 8 / 12 + 104;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 60;
    }
    return tmp;

    // right+up
  case 72:
  case 73:
  case 74:
  case 75:
  case 76:
  case 77:
  case 78:
  case 79:
  case 80:
  case 81:
  case 82:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = speedstep( mapIndex, 72, 12, update ) / 2;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 72 ) * 8 / 12 + 112;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 83:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = speedstep( mapIndex, 72, 12, update ) / 2;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 72 ) * 8 / 12 + 112;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 72;
    }
    return tmp;

    // right+down
  case 84:
  case 85:
  case 86:
  case 87:
  case 88:
  case 89:
  case 90:
  case 91:
  case 92:
  case 93:
  case 94:
    map_[ mapIndex ].obj_xoff = speedstep( mapIndex, 84, 12, update );
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 84 ) * 8 / 12 + 120;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 95:
    map_[ mapIndex ].obj_xoff = speedstep( mapIndex, 84, 12, update );
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 84 ) * 8 / 12 + 120;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 84;
    }
    return tmp;

    // turn up to left-up
  case 96:
  case 97:
  case 98:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 96 ) + 128;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 99:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 96 ) + 128;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 96;
    }
    return tmp;

    // turn left-up to up
  case 100:
  case 101:
  case 102:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 100 ) + 132;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 103:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 100 ) + 132;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 100;
    }
    return tmp;

    // turn up to right-up
  case 104:
  case 105:
  case 106:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 104 ) + 136;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 107:
    tmp = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 104 ) + 136;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 104;
    }
    return tmp;

    // turn right-up to right
  case 108:
  case 109:
  case 110:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 108 ) + 140;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 111:
    tmp = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 108 ) + 140;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 108;
    }
    return tmp;

    // turn down to left-down
  case 112:
  case 113:
  case 114:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 112 ) + 144;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 115:
    tmp = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 112 ) + 144;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 112;
    }
    return tmp;

    // turn left-down to left
  case 116:
  case 117:
  case 118:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 116 ) + 148;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 119:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 116 ) + 148;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 116;
    }
    return tmp;

    // turn down to right-down
  case 120:
  case 121:
  case 122:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 120 ) + 152;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 123:
    tmp = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 120 ) + 152;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 120;
    }
    return tmp;

    // turn right-down to down
  case 124:
  case 125:
  case 126:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 124 ) + 156;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 127:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 124 ) + 156;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 124;
    }
    return tmp;

    // turn left to left-up
  case 128:
  case 129:
  case 130:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 128 ) + 160;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 131:
    tmp = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 128 ) + 160;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 128;
    }
    return tmp;

    // turn left-up to up
  case 132:
  case 133:
  case 134:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 132 ) + 164;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 135:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 132 ) + 164;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 132;
    }
    return tmp;

    // turn left to left-down
  case 136:
  case 137:
  case 138:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 136 ) + 168;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 139:
    tmp = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 136 ) + 168;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 136;
    }
    return tmp;

    // turn left-down to down
  case 140:
  case 141:
  case 142:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 140 ) + 172;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 143:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 140 ) + 172;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 140;
    }
    return tmp;

    // turn right to right-up
  case 144:
  case 145:
  case 146:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 144 ) + 176;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 147:
    tmp = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 144 ) + 176;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 144;
    }
    return tmp;

    // turn right-up to up
  case 148:
  case 149:
  case 150:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 148 ) + 180;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 151:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 148 ) + 180;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 148;
    }
    return tmp;

    // turn right to right-down
  case 152:
  case 153:
  case 154:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 152 ) + 184;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 155:
    tmp = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 152 ) + 184;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 152;
    }
    return tmp;

    // turn right-down to down
  case 156:
  case 157:
  case 158:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 156 ) + 188;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 159:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 156 ) + 188;
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 156;
    }
    return tmp;

    // misc up
  case 160:
  case 161:
  case 162:
  case 163:
  case 164:
  case 165:
  case 166:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 160 ) + 192 +
          ( ( int ) ( stattab[ map_[ mapIndex ].ch_stat_off ] ) << 5 );
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 167:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 160 ) + 192 +
          ( ( int ) ( stattab[ map_[ mapIndex ].ch_stat_off ] ) << 5 );
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 160;
    }
    return tmp;

    // misc down
  case 168:
  case 169:
  case 170:
  case 171:
  case 172:
  case 173:
  case 174:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 168 ) + 200 +
          ( ( int ) ( stattab[ map_[ mapIndex ].ch_stat_off ] ) << 5 );
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 175:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 168 ) + 200 +
          ( ( int ) ( stattab[ map_[ mapIndex ].ch_stat_off ] ) << 5 );
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 168;
    }
    return tmp;

    // misc left
  case 176:
  case 177:
  case 178:
  case 179:
  case 180:
  case 181:
  case 182:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 176 ) + 208 +
          ( ( int ) ( stattab[ map_[ mapIndex ].ch_stat_off ] ) << 5 );
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 183:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 176 ) + 208 +
          ( ( int ) ( stattab[ map_[ mapIndex ].ch_stat_off ] ) << 5 );
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 176;
    }
    return tmp;

    // misc right
  case 184:
  case 185:
  case 186:
  case 187:
  case 188:
  case 189:
  case 190:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 184 ) + 216 +
          ( ( int ) ( stattab[ map_[ mapIndex ].ch_stat_off ] ) << 5 );
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status++;
    }
    return tmp;
  case 191:
    map_[ mapIndex ].obj_xoff = 0;
    map_[ mapIndex ].obj_yoff = 0;
    tmp                       = map_[ mapIndex ].ch_sprite + ( map_[ mapIndex ].ch_status - 184 ) + 216 +
          ( ( int ) ( stattab[ map_[ mapIndex ].ch_stat_off ] ) << 5 );
    if ( speedo( mapIndex ) && update )
    {
      map_[ mapIndex ].ch_status = 184;
    }
    return tmp;

  default:
    std::cerr << "Unknown ch_status " << map_[ mapIndex ].ch_status << std::endl;
    return map_[ mapIndex ].ch_sprite;
  }
}

// eng_item
int Map::interpolateItemSprite( int mapIndex )
{
  unsigned int ctick = ctick_;
  switch ( map_[ mapIndex ].it_status )
  {
  case 0:
    return map_[ mapIndex ].it_sprite;
  case 1:
    return map_[ mapIndex ].it_sprite;

    // four sprite animation, 2-step
  case 2:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite;

  case 3:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 2;

  case 4:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 4;

  case 5:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status = 2;
    }
    return map_[ mapIndex ].it_sprite + 6;

    // two sprite animation, 1-step
  case 6:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite;

  case 7:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status = 6;
    }
    return map_[ mapIndex ].it_sprite + 1;

    // eight sprite animation, 1-step
  case 8:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite;

  case 9:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 1;

  case 10:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 2;

  case 11:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 3;

  case 12:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 4;

  case 13:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 5;

  case 14:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 6;

  case 15:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status = 8;
    }
    return map_[ mapIndex ].it_sprite + 7;

    // five sprite animation, 1-step, random
  case 16:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite;

  case 17:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 1;

  case 18:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 2;

  case 19:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status++;
    }
    return map_[ mapIndex ].it_sprite + 3;

  case 20:
    if ( speedtab[ 10 ][ ctick ] )
    {
      map_[ mapIndex ].it_status = 16;
    }
    return map_[ mapIndex ].it_sprite + 4;

  case 21:
    return map_[ mapIndex ].it_sprite + ( ticker_ & 63 );

  default:
    std::cerr << "Unknown it_status\n";
    return map_[ mapIndex ].it_sprite;
  }
}

void Map::copysprite( int nr, int effect, int xpos, int ypos, int xoff, int yoff )
{
  if ( nr == 0 )
  {
    return;
  }

  ( void ) effect;

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

  // std::cerr << rx << ", " << ry << std::endl;

  for ( unsigned int y = 0; y < 1; y++ )
  {
    for ( unsigned int x = 0; x < 1; x++ ) // TODO: Why does only `1` work here, vs. the legacy xs ys values?
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