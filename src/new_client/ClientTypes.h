#ifndef CLIENT_TYPES_H
#define CLIENT_TYPES_H

struct look
{
  unsigned char  autoflag;
  unsigned short worn[20];
  unsigned short sprite;
  unsigned int   points;
  char           name[40];
  unsigned int   hp;
  unsigned int   end;
  unsigned int   mana;
  unsigned int   a_hp;
  unsigned int   a_end;
  unsigned int   a_mana;
  unsigned short nr;
  unsigned short id;
  unsigned char  extended;
  unsigned short item[62];
  unsigned int   price[62];
  unsigned int   pl_price;
};
static_assert(sizeof(look) == 496);

struct skilltab
{
  int  nr;
  char sortkey;
  char name[40];
  char desc[200];

  int attrib[3];
};
static_assert(sizeof(skilltab) == 260);

struct xbutton
{
  char name[8];
  int  skill_nr;
  //   int skill_strength;
};
static_assert(sizeof(xbutton) == 12);

struct pdata
{
  char cname[80];
  char ref[80];
  char desc[160];

  char changed;

  int            hide;
  int            show_names;
  int            show_proz;
  struct xbutton xbutton[12];
};
static_assert(sizeof(pdata) == 480);

// These values are zeroed out when the user selects "new character".  Presumably
// they have some intrinsic values if/when an MOA file is loaded.
struct key
{
  unsigned int usnr;
  unsigned int pass1, pass2;
  char         name[40];
  int          race;
};
static_assert(sizeof(key) == 56);

struct cmap
{
  // common:

  unsigned short x, y; // position

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

  int obj_xoff, obj_yoff;
  int ovl_xoff, ovl_yoff;

  int idle_ani;
};
static_assert(sizeof(cmap) == 64);

struct cplayer
{
  // informative stuff
  char name[40];

  int mode; // 0 = slow, 1 = medium, 2 = fast

  // character attributes+abilities
  // [0]=bare value, [1]=modifier, [2]=total value
  int attrib[5][6];
  int skill[100][6];
  int hp[6];
  int end[6];
  int mana[6];

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
  int item[40];
  int item_p[40];

  // items worn
  int worn[20];
  int worn_p[20];

  // spells ready
  int spell[20];
  int active[20];

  int armor;
  int weapon;

  int citem, citem_p;

  int attack_cn;
  int goto_x, goto_y;
  int misc_action, misc_target1, misc_target2;
  int dir;
};
static_assert(sizeof(cplayer) == 3348);

#endif