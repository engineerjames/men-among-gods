#include <json/json.h>

#include <cstdint>

#pragma pack( push, 1 )
struct item
{
  std::uint8_t used;               // 1
  char         name[ 40 ];         // 41
  char         reference[ 40 ];    // 81, a pair of boots
  char         description[ 200 ]; // 281, A pair of studded leather boots.

  unsigned long long flags; // 289, s.a.

  std::uint32_t value;     // 293, value to a merchant
  std::uint16_t placement; // 295, see constants above

  std::uint16_t temp; // 297, created from template temp

  unsigned char damage_state; // 298, has reached damage level X of 5, 0=OK, 4=almost destroyed, 5=destroyed

  // states for non-active [0] and active[1]
  std::uint32_t max_age[ 2 ];     // 306, maximum age per state
  std::uint32_t current_age[ 2 ]; // 314, current age in current state

  std::uint32_t max_damage;     // 318, maximum damage per state
  std::uint32_t current_damage; // 322, current damage in current state

  // modifiers - modifiers apply only when the item is being
  // worn (wearable objects) or when spell is cast. After duration expires,
  // the effects are removed.

  // modifiers - modifier [0] applies when the item is being
  // worn (wearable objects) or is added to the powers (spells) for permanent spells
  // modifier [1] applies when it is active
  // modifier [2] is not a modifier but the minimum value that attibute/skill must have to wear or use
  // the item

  char attrib[ 5 ][ 3 ]; // 337

  std::int16_t hp[ 3 ];   // 343
  std::int16_t end[ 3 ];  // 349
  std::int16_t mana[ 3 ]; // 355

  char skill[ 50 ][ 3 ]; // 505

  char armor[ 2 ];  // 506
  char weapon[ 2 ]; // 507

  std::int16_t light[ 2 ]; // 511

  std::uint32_t duration; // 515
  std::uint32_t cost;     // 519
  std::uint32_t power;    // 523
  std::uint32_t active;   // 527

  // map stuff
  std::uint16_t x, y;            // 531, current position        NOTE: x=0, y=0 = void
  std::uint16_t carried;         // 533, carried by character carried
  std::uint16_t sprite_override; // 535, used for potions/spells which change the character sprite

  std::int16_t  sprite[ 2 ]; // 543
  unsigned char status[ 2 ]; // 545

  char gethit_dam[ 2 ]; // 547, damage for hitting this item

  char min_rank; // minimum rank to wear the item
  char future[ 3 ];
  int  future3[ 9 ]; // 587

  int t_bought; // 591
  int t_sold;   // 595

  unsigned char driver;     // 596, special routines for LOOKSPECIAL and USESPECIAL
  std::uint32_t data[ 10 ]; // 634, driver data

  Json::Value toJson() const
  {
    Json::Value root {};

    root[ "used" ]        = used;
    root[ "name" ]        = name;
    root[ "reference" ]   = reference;
    root[ "description" ] = description;

    // TODO: Breakout into the actual item flags...
    root[ "flags" ] = static_cast< int >( flags );

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
  std::uint8_t used; // 1
  // general

  char name[ 40 ];         // 41
  char reference[ 40 ];    // 81
  char description[ 200 ]; // 281

  std::int32_t kindred; // 285

  std::int32_t  player;       // 289
  std::uint32_t pass1, pass2; // 297

  std::uint16_t sprite; // 299, sprite base value, 1024 dist
  std::uint16_t sound;  // 301, sound base value, 64 dist

  std::uint64_t flags; // 309

  std::int16_t alignment; // 311

  std::uint16_t temple_x; // 313, position of temple for recall and dying
  std::uint16_t temple_y; // 315

  std::uint16_t tavern_x; // 317, position of last temple for re-login
  std::uint16_t tavern_y; // 319

  std::uint16_t temp; // 321, created from template n

  // character stats
  // [0]=bare value, 0=unknown
  // [1]=preset modifier, is race/npc dependend
  // [2]=race specific maximum
  // [3]=race specific difficulty to raise (0=not raisable, 1=easy ... 10=hard)
  // [4]=dynamic modifier, depends on equipment and spells (this one is currently not used)
  // [5]=total value

  unsigned char attrib[ 5 ][ 6 ]; // 351

  std::uint16_t hp[ 6 ];   // 363
  std::uint16_t end[ 6 ];  // 375
  std::uint16_t mana[ 6 ]; // 387

  unsigned char skill[ 50 ][ 6 ]; // 687

  unsigned char weapon_bonus;
  unsigned char armor_bonus;

  // temporary attributes
  std::int32_t a_hp;
  std::int32_t a_end;
  std::int32_t a_mana;

  unsigned char light; // strength of lightsource
  unsigned char mode;  // 0 = slow, 1 = medium, 2 = fast
  std::int16_t  speed;

  std::int32_t points;
  std::int32_t points_tot;

  // summary of weapons + armor
  std::int16_t armor;
  std::int16_t weapon;

  // map stuff
  std::int16_t  x, y;     // current position x,y NOTE: x=-1, y=-1 = void
  std::int16_t  tox, toy; // target coordinated, where the char will be next turn
  std::int16_t  frx, fry; // where the char was last turn
  std::int16_t  status;   // what the character is doing, animation-wise
  std::int16_t  status2;  // for plr_misc(): what is misc?
  unsigned char dir;      // direction character is facing

  // posessions
  std::int32_t gold;

  // items carried
  std::uint32_t item[ 40 ];

  // items worn
  std::uint32_t worn[ 20 ];

  // spells active on character
  std::uint32_t spell[ 20 ];

  // item currently in hand (mouse cursor)
  std::uint32_t citem;

  // In reality this should be time_t
  std::uint32_t creation_date;

  // In reality this should be time_t
  std::uint32_t login_date;

  std::uint32_t addr;

  // misc
  std::uint32_t current_online_time;
  std::uint32_t total_online_time;
  std::uint32_t comp_volume;
  std::uint32_t raw_volume;
  std::uint32_t idle;

  // generic driver data
  std::uint16_t attack_cn;     // target for attacks, will attack if set (prio 4)
  std::uint16_t skill_nr;      // skill to use/spell to cast, will cast if set (prio 2)
  std::uint16_t skill_target1; // target for skills/spells
  std::uint16_t skill_target2; // target for skills/spells
  std::uint16_t goto_x;        // will goto x,y if set (prio 3)
  std::uint16_t goto_y;
  std::uint16_t use_nr; // will use worn item nr if set (prio 1)

  std::uint16_t misc_action;  // drop, pickup, use, whatever (prio 5)
  std::uint16_t misc_target1; // item for misc_action
  std::uint16_t misc_target2; // location for misc_action

  std::uint16_t cerrno; // error/success indicator for last action (svr_act level)

  std::uint16_t escape_timer;  // can try again to escape in X ticks
  std::uint16_t enemy[ 4 ];    // currently being fought against by these
  std::uint16_t current_enemy; // currently fighting against X

  std::uint16_t retry; // retry current action X times

  std::uint16_t stunned; // is stunned for X ticks

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

  std::int16_t sprite_override;

  std::int16_t future2[ 49 ];

  std::uint32_t depot[ 62 ];

  std::int32_t depot_cost;

  std::int32_t luck;

  std::int32_t unreach;
  std::int32_t unreachx;
  std::int32_t unreachy;

  std::int32_t monsterClass; // monster class

  std::int32_t future3[ 12 ];

  // In reality this should be time_t
  std::uint32_t logout_date;

  // driver data
  std::int32_t data[ 100 ];
  char         text[ 10 ][ 160 ];

  Json::Value toJson() const
  {
    Json::Value root {};

    root[ "used" ]        = used;
    root[ "name" ]        = name;
    root[ "reference" ]   = reference;
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
    root[ "hp" ]   = Json::arrayValue;
    root[ "end" ]  = Json::arrayValue;
    root[ "mana" ] = Json::arrayValue;

    for ( int i = 0; i < 6; ++i )
    {
      root[ "hp" ][ i ]   = hp[ i ];
      root[ "end" ][ i ]  = end[ i ];
      root[ "mana" ][ i ] = mana[ i ];
    }

    // TODO: Add in skills

    root[ "weapon_bonus" ] = weapon_bonus;
    root[ "armor_bonus" ]  = armor_bonus;
    root[ "a_hp" ]         = a_hp;
    root[ "a_end" ]        = a_end;
    root[ "a_mana" ]       = a_mana;
    root[ "light" ]        = light;
    root[ "mode" ]         = mode;
    root[ "speed" ]        = speed;
    root[ "points" ]       = points;
    root[ "points_tot" ]   = points;
    root[ "armor" ]        = armor;
    root[ "weapon" ]       = weapon;
    root[ "x" ]            = x;
    root[ "y" ]            = y;
    root[ "tox" ]          = tox;
    root[ "toy" ]          = toy;
    root[ "frx" ]          = frx;
    root[ "fry" ]          = fry;
    root[ "status" ]       = status;
    root[ "dir" ]          = dir;
    root[ "gold" ]         = gold;

    // TODO: Add items carried, and active spells

    root[ "worn" ] = Json::arrayValue;
    for ( int i = 0; i < 20; ++i )
    {
      root[ "worn" ][ i ] = worn[ i ];
    }

    root[ "citem" ]               = citem;
    root[ "creation_date" ]       = creation_date;
    root[ "login_date" ]          = login_date;
    root[ "addr" ]                = addr;
    root[ "current_online_time" ] = current_online_time;
    root[ "total_online_time" ]   = total_online_time;
    root[ "comp_volume" ]         = comp_volume;
    root[ "raw_volume" ]          = raw_volume;
    root[ "idle" ]                = idle;
    root[ "attack_cn" ]           = attack_cn;
    root[ "skill_nr" ]            = skill_nr;
    root[ "skill_target1" ]       = skill_target1;
    root[ "skill_target2" ]       = skill_target2;
    root[ "goto_x" ]              = goto_x;
    root[ "goto_y" ]              = goto_y;
    root[ "use_nr" ]              = use_nr;
    root[ "misc_action" ]         = misc_action;
    root[ "misc_target1" ]        = misc_target1;
    root[ "misc_target2" ]        = misc_target2;
    root[ "cerrno" ]              = cerrno;
    root[ "escape_timer" ]        = escape_timer;

    root[ "enemy" ] = Json::arrayValue;
    for ( int i = 0; i < 4; ++i )
    {
      root[ "enemy" ][ i ] = enemy[ i ];
    }

    root[ "current_enemy" ] = current_enemy;
    root[ "retry" ]         = retry;
    root[ "stunned" ]       = stunned;
    root[ "speed_mod" ]     = speed_mod;
    root[ "last_action" ]   = last_action;
    root[ "unused" ]        = unused;
    root[ "depot_sold" ]    = depot_sold;
    root[ "gethit_dam" ]    = gethit_dam;
    root[ "gethit_bonus" ]  = gethit_bonus;
    root[ "light_bonus" ]   = light_bonus;
    root[ "password" ]      = passwd;
    root[ "lastattack" ]    = lastattack;

    // TODO: Add future1, future2, depot
    root[ "sprite_override" ] = sprite_override;
    root[ "depot_cost" ]      = depot_cost;
    root[ "luck" ]            = luck;
    root[ "unreach" ]         = unreach;
    root[ "unreach_x" ]       = unreachx;
    root[ "unreach_y" ]       = unreachy;
    root[ "monsterClass" ]    = monsterClass;

    // TODO: add future3, data, and text?

    return root;
  }
};
#pragma pack( pop )