#ifndef CLIENT_TYPES_H
#define CLIENT_TYPES_H

#include <fstream>
#include <iostream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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

struct skilltab
{
  int  nr;
  char sortkey;
  char name[ 40 ];
  char desc[ 200 ];

  int attrib[ 3 ];
};
static_assert( sizeof( skilltab ) == 260 );

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
  INFO, // Yellow
  CHAT, // Blue
  LOG,  // Green
  ERROR // Red
};

inline LogType getLogType( int value )
{
  if ( value >= 0 && value <= 3 )
  {
    return static_cast< LogType >( value );
  }
  else
  {
    std::cerr << "UNABLE TO PARSE LOG TYPE!\n" << std::endl;
    return LogType::ERROR;
  }
}

template < class Archive > void serialize( Archive& ar, cmap& theMap, const unsigned int )
{
  ar& theMap.x;
  ar& theMap.y;
  ar& theMap.ba_sprite;
  ar& theMap.light;
  ar& theMap.flags;
  ar& theMap.flags2;
  ar& theMap.ch_sprite;
  ar& theMap.ch_status;
  ar& theMap.ch_stat_off;
  ar& theMap.ch_speed;
  ar& theMap.ch_nr;
  ar& theMap.ch_id;
  ar& theMap.ch_proz;
  ar& theMap.it_sprite;
  ar& theMap.it_status;
  ar& theMap.back;
  ar& theMap.obj1;
  ar& theMap.obj2;
  ar& theMap.obj_xoff;
  ar& theMap.obj_yoff;
  ar& theMap.ovl_xoff;
  ar& theMap.ovl_yoff;
}

struct cplayer
{
  // informative stuff
  char name[ 40 ];

  int mode; // 0 = slow, 1 = medium, 2 = fast

  // character attributes+abilities
  // [0]=bare value, [1]=modifier, [2]=total value
  // ^ Originally documented--at least partially wrong
  // Below are the correct notations
  // [0]=Base value (unmodified)
  // [3]=Cost multiplier (in terms of experience points)
  // [5]=Total value (displayed to user)
  int attrib[ 5 ][ 6 ];
  int skill[ 100 ][ 6 ];
  int hp[ 6 ];
  int end[ 6 ];
  int mana[ 6 ];

  // temporary attributes
  int a_hp;
  int a_end;
  int a_mana;

  int points;
  int points_tot;
  int kindred;

  // posessions
  int gold;

  // items carried
  int item[ 40 ];
  int item_p[ 40 ];

  // items worn
  int worn[ 20 ];
  int worn_p[ 20 ];

  // spells ready
  int spell[ 20 ];
  int active[ 20 ];

  int armor;
  int weapon;

  int citem;
  int citem_p;

  int attack_cn;
  int goto_x;
  int goto_y;
  int misc_action;
  int misc_target1;
  int misc_target2;
  int dir;
};
static_assert( sizeof( cplayer ) == 3348 );

template < class Archive > void serialize( Archive& ar, cplayer& thePlayer, const unsigned int )
{
  ar& thePlayer.name;
  ar& thePlayer.mode;
  ar& thePlayer.attrib;
  ar& thePlayer.skill;
  ar& thePlayer.hp;
  ar& thePlayer.end;
  ar& thePlayer.mana;
  ar& thePlayer.a_hp;
  ar& thePlayer.a_end;
  ar& thePlayer.a_mana;
  ar& thePlayer.points;
  ar& thePlayer.points_tot;
  ar& thePlayer.kindred;
  ar& thePlayer.gold;
  ar& thePlayer.item;
  ar& thePlayer.item_p;
  ar& thePlayer.worn;
  ar& thePlayer.worn_p;
  ar& thePlayer.spell;
  ar& thePlayer.active;
  ar& thePlayer.armor;
  ar& thePlayer.weapon;
  ar& thePlayer.citem;
  ar& thePlayer.citem_p;
  ar& thePlayer.attack_cn;
  ar& thePlayer.goto_x;
  ar& thePlayer.goto_y;
  ar& thePlayer.misc_action;
  ar& thePlayer.misc_target1;
  ar& thePlayer.misc_target2;
  ar& thePlayer.dir;
}

#endif