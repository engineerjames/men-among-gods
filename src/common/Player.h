#ifndef MEN_AMONG_GODS_PLAYER_H
#define MEN_AMONG_GODS_PLAYER_H

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


#endif