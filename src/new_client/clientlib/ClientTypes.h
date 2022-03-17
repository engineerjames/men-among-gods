#ifndef CLIENT_TYPES_H
#define CLIENT_TYPES_H

#include <fstream>
#include <tuple>

#include "Logger.h"

struct look
{
  unsigned char  autoflag;
  unsigned short worn[ 20 ];
  unsigned short sprite;
  unsigned int   points;
  char           name[ 40 ];
  unsigned int   hp;
  unsigned int   end;
  unsigned int   mana;
  unsigned int   a_hp;
  unsigned int   a_end;
  unsigned int   a_mana;
  unsigned short nr;
  unsigned short id;
  unsigned char  extended;
  unsigned short item[ 62 ];
  unsigned int   price[ 62 ];
  unsigned int   pl_price;
};
static_assert( sizeof( look ) == 496 );

// What is the significance of looks vs. look?
struct looks
{
  char           known;
  char           name[ 21 ];
  char           proz;
  unsigned short id;
};

struct xbutton
{
  char name[ 8 ];
  int  skill_nr;
  //   int skill_strength;
};
static_assert( sizeof( xbutton ) == 12 );

struct pdata
{
  char cname[ 80 ];
  char ref[ 80 ];
  char desc[ 160 ];

  char changed;

  int            hide;
  int            show_names;
  int            show_proz;
  struct xbutton xbutton[ 12 ];
};
static_assert( sizeof( pdata ) == 480 );

// These values are zeroed out when the user selects "new character".  Presumably
// they have some intrinsic values if/when an MOA file is loaded.
struct key
{
  unsigned int usnr;
  unsigned int pass1, pass2;
  char         name[ 40 ];
  int          race;
};
static_assert( sizeof( key ) == 56 );

struct cmap
{
  // common:

  unsigned short x;
  unsigned short y; // position

  // for background
  short int     ba_sprite; // background image
  unsigned char light;
  unsigned int  flags;
  unsigned int  flags2;

  // for character
  unsigned short ch_sprite; // basic sprite of character
  unsigned char  ch_status; // what the character is doing, animation-wise
  unsigned char  ch_stat_off;
  unsigned char  ch_speed; // speed of animation
  unsigned short ch_nr;    // character id
  unsigned short ch_id;    // character 'crc'
  unsigned char  ch_proz;

  // for item
  short int     it_sprite; // basic sprite of item
  unsigned char it_status; // for items with animation (burning torches etc)

  // for local computation -- client only:
  int back; // background
  int obj1; // item
  int obj2; // character

  int obj_xoff;
  int obj_yoff;
  int ovl_xoff;
  int ovl_yoff;

  int idle_ani;
};
static_assert( sizeof( cmap ) == 64 );

enum struct LogType
{
  ERROR, // Red
  INFO,  // Yellow
  LOG,   // Green
  CHAT   // Blue
};

inline LogType getLogType( int value )
{
  if ( value >= 0 && value <= 3 )
  {
    return static_cast< LogType >( value );
  }
  else
  {
    LOG_ERROR( "Unable to parse log type" );
    return LogType::ERROR;
  }
}

#endif