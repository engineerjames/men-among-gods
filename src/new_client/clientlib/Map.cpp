#include "Map.h"

#include <array>

#include "Constants.h"
#include "Logger.h"
#include "MapConstants.h"

namespace
{
const std::array< std::array< unsigned char, 20 >, 20 > speedtab = {
    //  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
    { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // 20
      { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // 19
      { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },  // 18
      { 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 },  // 17
      { 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1 },  // 16
      { 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1 },  // 15
      { 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1 },  // 14
      { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 },  // 13
      { 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 },  // 12
      { 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1 },  // 11
      { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },  // 10
      { 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0 },  // 9
      { 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0 },  // 8
      { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },  // 7
      { 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 },  // 6
      { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 },  // 5
      { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },  // 4
      { 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },  // 3
      { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },  // 2
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } } // 1
};

//  0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10
static const std::array< int, 11 > stattab = { 0, 1, 1, 6, 6, 2, 3, 4, 5, 7, 4 };

int do_idle( int ani, int sprite )
{
  return sprite == 22480 ? ani : 0;
}

} // namespace

namespace MenAmongGods
{
Map::Map()
    : map_()
    , ctick_()
    , ticker_()
{
  for ( unsigned int i = 0; i < MAPX * MAPY; ++i )
  {
    map_[ i ].ba_sprite = SPR_EMPTY;
  }
}

unsigned short Map::getX( int index ) const
{
  return map_[ index ].x;
}

unsigned short Map::getY( int index ) const
{
  return map_[ index ].y;
}

short int Map::getBackgroundSprite( int index ) const
{
  return map_[ index ].ba_sprite;
}

unsigned char Map::getLight( int index ) const
{
  return map_[ index ].light;
}

unsigned int Map::getFlags( int index ) const
{
  return map_[ index ].flags;
}

unsigned int Map::getFlags2( int index ) const
{
  return map_[ index ].flags2;
}

unsigned short Map::getCharacterSprite( int index ) const
{
  return map_[ index ].ch_sprite;
}

unsigned char Map::getCharacterStatus( int index ) const
{
  return map_[ index ].ch_status;
}

unsigned char Map::getCharacterStatOff( int index ) const
{
  return map_[ index ].ch_stat_off;
}

unsigned char Map::getCharacterSpeed( int index ) const
{
  return map_[ index ].ch_speed;
}

unsigned short Map::getCharacterId( int index ) const
{
  return map_[ index ].ch_nr;
}

unsigned short Map::getCharacterCrc( int index ) const
{
  return map_[ index ].ch_id;
}

unsigned char Map::getCharacterPercentHealth( int index ) const
{
  return map_[ index ].ch_proz;
}

short int Map::getItemSprite( int index ) const
{
  return map_[ index ].it_sprite;
}

unsigned char Map::getItemStatus( int index ) const
{
  return map_[ index ].it_status;
}

int Map::getBackground( int index ) const
{
  return map_[ index ].back;
}

int Map::getObject1( int index ) const
{
  return map_[ index ].obj1;
}

int Map::getObject2( int index ) const
{
  return map_[ index ].obj2;
}

int Map::getObjectXOffset( int index ) const
{
  return map_[ index ].obj_xoff;
}

int Map::getObjectYOffset( int index ) const
{
  return map_[ index ].obj_yoff;
}

int Map::getOvlXOffset( int index ) const
{
  return map_[ index ].ovl_xoff;
}

int Map::getOvlYOffset( int index ) const
{
  return map_[ index ].ovl_yoff;
}

int Map::getIdleAnimation( int index ) const
{
  return map_[ index ].idle_ani;
}

void Map::setX( int index, unsigned short newValue )
{
  map_[ index ].x = newValue;
}

void Map::setY( int index, unsigned short newValue )
{
  map_[ index ].y = newValue;
}

void Map::setBackgroundSprite( int index, short int newValue )
{
  map_[ index ].ba_sprite = newValue;
}

void Map::setLight( int index, unsigned char newValue )
{
  map_[ index ].light = newValue;
}

void Map::setFlags( int index, unsigned int newValue )
{
  map_[ index ].flags = newValue;
}

void Map::setFlags2( int index, unsigned int newValue )
{
  map_[ index ].flags2 = newValue;
}

void Map::setCharacterSprite( int index, unsigned short newValue )
{
  map_[ index ].ch_sprite = newValue;
}

void Map::setCharacterStatus( int index, unsigned char newValue )
{
  map_[ index ].ch_status = newValue;
}

void Map::setCharacterStatOff( int index, unsigned char newValue )
{
  map_[ index ].ch_stat_off = newValue;
}

void Map::setCharacterSpeed( int index, unsigned char newValue )
{
  map_[ index ].ch_speed = newValue;
}

void Map::setCharacterId( int index, unsigned short newValue )
{
  map_[ index ].ch_nr = newValue;
}

void Map::setCharacterCrc( int index, unsigned short newValue )
{
  map_[ index ].ch_id = newValue;
}

void Map::setCharacterPercentHealth( int index, unsigned char newValue )
{
  map_[ index ].ch_proz = newValue;
}

void Map::setItemSprite( int index, short int newValue )
{
  map_[ index ].it_sprite = newValue;
}

void Map::setItemStatus( int index, unsigned char newValue )
{
  map_[ index ].it_status = newValue;
}

void Map::setBackground( int index, int newValue )
{
  map_[ index ].back = newValue;
}

void Map::setObject1( int index, int newValue )
{
  map_[ index ].obj1 = newValue;
}

void Map::setObject2( int index, int newValue )
{
  map_[ index ].obj2 = newValue;
}

void Map::setObjectXOffset( int index, int newValue )
{
  map_[ index ].obj_xoff = newValue;
}

void Map::setObjectYOffset( int index, int newValue )
{
  map_[ index ].obj_yoff = newValue;
}

void Map::setOvlXOffset( int index, int newValue )
{
  map_[ index ].ovl_xoff = newValue;
}

void Map::setOvlYOffset( int index, int newValue )
{
  map_[ index ].ovl_yoff = newValue;
}

void Map::setIdleAnimation( int index, int newValue )
{
  map_[ index ].idle_ani = newValue;
}

void Map::scrollRight()
{
  std::memmove( map_.data(), map_.data() + 1, sizeof( struct cmap ) * ( TILEX * TILEY - 1 ) );
}

void Map::scrollLeft()
{
  std::memmove( map_.data() + 1, map_.data(), sizeof( struct cmap ) * ( TILEX * TILEY - 1 ) );
}

void Map::scrollDown()
{
  memmove( map_.data(), map_.data() + TILEX, sizeof( struct cmap ) * ( TILEX * TILEY - TILEX ) );
}

void Map::scrollUp()
{
  memmove( map_.data() + TILEX, map_.data(), sizeof( struct cmap ) * ( TILEX * TILEY - TILEX ) );
}

void Map::scrollLeftUp()
{
  memmove( map_.data() + TILEX + 1, map_.data(), sizeof( struct cmap ) * ( TILEX * TILEY - TILEX - 1 ) );
}

void Map::scrollLeftDown()
{
  memmove( map_.data(), map_.data() + TILEX - 1, sizeof( struct cmap ) * ( TILEX * TILEY - TILEX + 1 ) );
}

void Map::scrollRightUp()
{
  memmove( map_.data() + TILEX - 1, map_.data(), sizeof( struct cmap ) * ( TILEX * TILEY - TILEX + 1 ) );
}

void Map::scrollRightDown()
{
  memmove( map_.data(), map_.data() + TILEX + 1, sizeof( struct cmap ) * ( TILEX * TILEY - TILEX - 1 ) );
}

cmap Map::getMap( int index ) const
{
  if ( index < 0 || index >= static_cast< int >( map_.size() ) )
  {
    return cmap {};
  }

  return map_[ index ];
}

void Map::setMap( int index, cmap newValue )
{
  map_[ index ] = newValue;
}

void Map::tick()
{
  ticker_++; // Should this be at the end?

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
}

int Map::speedo( unsigned int n )
{
  return speedtab[ map_[ n ].ch_speed ][ ctick_ ];
}

void Map::setCTick( int newValue )
{
  ctick_ = newValue;
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

int Map::interpolateItemSprite( unsigned int mapIndex )
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
    LOG_ERROR( "Unknown it_status" );
    return map_[ mapIndex ].it_sprite;
  }
}

int Map::interpolateCharacterSprite( unsigned int mapIndex )
{
  int tmp {};
  int update = 1;

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
    LOG_ERROR( "Unknown ch_status " << map_[ mapIndex ].ch_status );
    return map_[ mapIndex ].ch_sprite;
  }
}

} // namespace MenAmongGods