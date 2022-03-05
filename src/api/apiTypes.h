#include <json/json.h>

#pragma pack( push, 1 )
struct item
{
  unsigned char used;               // 1
  char          name[ 40 ];         // 41
  char          reference[ 40 ];    // 81, a pair of boots
  char          description[ 200 ]; // 281, A pair of studded leather boots.

  unsigned long long flags; // 289, s.a.

  unsigned int   value;     // 293, value to a merchant
  unsigned short placement; // 295, see constants above

  unsigned short temp; // 297, created from template temp

  unsigned char damage_state; // 298, has reached damage level X of 5, 0=OK, 4=almost destroyed, 5=destroyed

  // states for non-active [0] and active[1]
  unsigned int max_age[ 2 ];     // 306, maximum age per state
  unsigned int current_age[ 2 ]; // 314, current age in current state

  unsigned int max_damage;     // 318, maximum damage per state
  unsigned int current_damage; // 322, current damage in current state

  // modifiers - modifiers apply only when the item is being
  // worn (wearable objects) or when spell is cast. After duration expires,
  // the effects are removed.

  // modifiers - modifier [0] applies when the item is being
  // worn (wearable objects) or is added to the powers (spells) for permanent spells
  // modifier [1] applies when it is active
  // modifier [2] is not a modifier but the minimum value that attibute/skill must have to wear or use
  // the item

  char attrib[ 5 ][ 3 ]; // 337

  short hp[ 3 ];   // 343
  short end[ 3 ];  // 349
  short mana[ 3 ]; // 355

  char skill[ 50 ][ 3 ]; // 505

  char armor[ 2 ];  // 506
  char weapon[ 2 ]; // 507

  short light[ 2 ]; // 511

  unsigned int duration; // 515
  unsigned int cost;     // 519
  unsigned int power;    // 523
  unsigned int active;   // 527

  // map stuff
  unsigned short int x, y;            // 531, current position        NOTE: x=0, y=0 = void
  unsigned short     carried;         // 533, carried by character carried
  unsigned short     sprite_override; // 535, used for potions/spells which change the character sprite

  short int     sprite[ 2 ]; // 543
  unsigned char status[ 2 ]; // 545

  char gethit_dam[ 2 ]; // 547, damage for hitting this item

  char min_rank; // minimum rank to wear the item
  char future[ 3 ];
  int  future3[ 9 ]; // 587

  int t_bought; // 591
  int t_sold;   // 595

  unsigned char driver;     // 596, special routines for LOOKSPECIAL and USESPECIAL
  unsigned int  data[ 10 ]; // 634, driver data

  Json::Value toJson() const
  {
    Json::Value root {};

    root[ "used" ]        = used;
    root[ "name" ]        = name;
    root[ "reference" ]   = reference;
    root[ "description" ] = description;

    // TODO: Breakout into the actual item flags...
    root[ "flags" ] = flags;

    root[ "value" ]        = value;
    root[ "placement" ]    = placement;
    root[ "temp" ]         = temp;
    root[ "damage_state" ] = damage_state;

    root[ "max_age" ]      = Json::arrayValue;
    root[ "max_age" ][ 0 ] = max_age[ 0 ];
    root[ "max_age" ][ 1 ] = max_age[ 1 ];

    root[ "current_age" ]      = Json::arrayValue;
    root[ "current_age" ][ 0 ] = current_age[ 0 ];
    root[ "current_age" ][ 1 ] = current_age[ 1 ];

    root[ "current_damage" ] = current_damage;
    root[ "max_damage" ]     = max_damage;

    // TODO: Fill this out
    root[ "attributes" ] = Json::arrayValue;

    root[ "hp" ]   = Json::arrayValue;
    root[ "end" ]  = Json::arrayValue;
    root[ "mana" ] = Json::arrayValue;

    for ( int i = 0; i < 3; ++i )
    {
      root[ "hp" ][ i ]   = hp[ i ];
      root[ "end" ][ i ]  = end[ i ];
      root[ "mana" ][ i ] = mana[ i ];
    }

    // TODO: Fill this out
    root[ "skills" ] = Json::arrayValue;

    root[ "armor" ]      = Json::arrayValue;
    root[ "weapon" ]     = Json::arrayValue;
    root[ "light" ]      = Json::arrayValue;
    root[ "sprite" ]     = Json::arrayValue;
    root[ "status" ]     = Json::arrayValue;
    root[ "gethit_dam" ] = Json::arrayValue;

    for ( int i = 0; i < 2; ++i )
    {
      root[ "armor" ][ i ]      = armor[ i ];
      root[ "weapon" ][ i ]     = weapon[ i ];
      root[ "light" ][ i ]      = light[ i ];
      root[ "sprite" ][ i ]     = sprite[ i ];
      root[ "status" ][ i ]     = status[ i ];
      root[ "gethit_dam" ][ i ] = gethit_dam[ i ];
    }

    root[ "duration" ]        = duration;
    root[ "cost" ]            = cost;
    root[ "power" ]           = power;
    root[ "active" ]          = active;
    root[ "x" ]               = x;
    root[ "y" ]               = y;
    root[ "carried" ]         = carried;
    root[ "sprite_override" ] = sprite_override;
    root[ "min_rank" ]        = min_rank;

    // TODO: Add in future and future 3

    root[ "t_bought" ] = t_bought;
    root[ "t_sold" ]   = t_sold;
    root[ "driver" ]   = driver;

    root[ "data" ] = Json::arrayValue;

    for ( int i = 0; i < 10; ++i )
    {
      root[ "data" ][ i ] = data[ i ];
    }

    return root;
  }
};
#pragma pack( pop )

#pragma pack( push, 1 )
struct character
{
  unsigned char used; // 1
  // general

  char name[ 40 ];         // 41
  char reference[ 40 ];    // 81
  char description[ 200 ]; // 281

  int kindred; // 285

  int          player;       // 289
  unsigned int pass1, pass2; // 297

  unsigned short sprite; // 299, sprite base value, 1024 dist
  unsigned short sound;  // 301, sound base value, 64 dist

  unsigned long long flags; // 309

  short int alignment; // 311

  unsigned short temple_x; // 313, position of temple for recall and dying
  unsigned short temple_y; // 315

  unsigned short tavern_x; // 317, position of last temple for re-login
  unsigned short tavern_y; // 319

  unsigned short temp; // 321, created from template n

  // character stats
  // [0]=bare value, 0=unknown
  // [1]=preset modifier, is race/npc dependend
  // [2]=race specific maximum
  // [3]=race specific difficulty to raise (0=not raisable, 1=easy ... 10=hard)
  // [4]=dynamic modifier, depends on equipment and spells (this one is currently not used)
  // [5]=total value

  unsigned char attrib[ 5 ][ 6 ]; // 351

  unsigned short hp[ 6 ];   // 363
  unsigned short end[ 6 ];  // 375
  unsigned short mana[ 6 ]; // 387

  unsigned char skill[ 50 ][ 6 ]; // 687

  unsigned char weapon_bonus;
  unsigned char armor_bonus;

  // temporary attributes
  int a_hp;
  int a_end;
  int a_mana;

  unsigned char light; // strength of lightsource
  unsigned char mode;  // 0 = slow, 1 = medium, 2 = fast
  short int     speed;

  int points;
  int points_tot;

  // summary of weapons + armor
  short int armor;
  short int weapon;

  // map stuff
  short int     x, y;     // current position x,y NOTE: x=-1, y=-1 = void
  short int     tox, toy; // target coordinated, where the char will be next turn
  short int     frx, fry; // where the char was last turn
  short int     status;   // what the character is doing, animation-wise
  short int     status2;  // for plr_misc(): what is misc?
  unsigned char dir;      // direction character is facing

  // posessions
  int gold;

  // items carried
  unsigned int item[ 40 ];

  // items worn
  unsigned int worn[ 20 ];

  // spells active on character
  unsigned int spell[ 20 ];

  // item currently in hand (mouse cursor)
  unsigned int citem;

  time_t creation_date;
  time_t login_date;

  unsigned int addr;

  // misc
  unsigned int current_online_time;
  unsigned int total_online_time;
  unsigned int comp_volume;
  unsigned int raw_volume;
  unsigned int idle;

  // generic driver data
  unsigned short attack_cn;     // target for attacks, will attack if set (prio 4)
  unsigned short skill_nr;      // skill to use/spell to cast, will cast if set (prio 2)
  unsigned short skill_target1; // target for skills/spells
  unsigned short skill_target2; // target for skills/spells
  unsigned short goto_x;        // will goto x,y if set (prio 3)
  unsigned short goto_y;
  unsigned short use_nr; // will use worn item nr if set (prio 1)

  unsigned short misc_action;  // drop, pickup, use, whatever (prio 5)
  unsigned short misc_target1; // item for misc_action
  unsigned short misc_target2; // location for misc_action

  unsigned short cerrno; // error/success indicator for last action (svr_act level)

  unsigned short escape_timer;  // can try again to escape in X ticks
  unsigned short enemy[ 4 ];    // currently being fought against by these
  unsigned short current_enemy; // currently fighting against X

  unsigned short retry; // retry current action X times

  unsigned short stunned; // is stunned for X ticks

  // misc stuff added later:
  char speed_mod;   // race dependand speed modification
  char last_action; // last action was success/failure (driver_generic level)
  char unused;
  char depot_sold; // items from depot where sold to pay for the rent

  char gethit_dam;   // damage for attacker when hitting this char
  char gethit_bonus; // race specific bonus for above

  unsigned char light_bonus; // char emits light all the time

  char passwd[ 16 ];

  char lastattack;    // neater display: remembers the last attack animation
  char future1[ 25 ]; // space for future expansion

  short int sprite_override;

  short future2[ 49 ];

  unsigned int depot[ 62 ];

  int depot_cost;

  int luck;

  int unreach;
  int unreachx;
  int unreachy;

  int monsterClass; // monster class

  int future3[ 12 ];

  time_t logout_date;

  // driver data
  int  data[ 100 ];
  char text[ 10 ][ 160 ];

  Json::Value toJson() const
  {
    Json::Value root {};

    root[ "used" ] = used;
    root[ "name" ] = name;
    root[ "reference" ] = reference;
    root[ "description" ] = description;
    root[ "kindred" ]     = kindred;
    root[ "player" ]      = player;
    root[ "pass1" ]       = pass1;
    root[ "pass2" ]       = pass2;
    root[ "sprite" ]      = sprite;
    root[ "sound" ]       = sound;
    root[ "flags" ]       = flags;
    root[ "alignment" ]   = alignment;
    root[ "temple_x" ]    = temple_x;
    root[ "temple_y" ]    = temple_y;
    root[ "tavern_x" ]    = tavern_x;
    root[ "tavern_y" ]    = tavern_y;
    root[ "temp" ]        = temp;
    
    // TODO: Fill in attributes
    root[ "hp" ] = Json::arrayValue;
    root[ "end" ] = Json::arrayValue;
    root[ "mana" ] = Json::arrayValue;

    for (int i = 0; i < 6; ++i)
    {
      root[ "hp" ][ i ] = hp[ i ];
      root[ "end" ][ i ] = end[ i ];
      root[ "mana" ][ i ] = mana[ i ];
    }

    // TODO: Add in skills

  }
};
#pragma pack( pop )
