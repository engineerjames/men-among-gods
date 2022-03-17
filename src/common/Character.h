#ifndef MEN_AMONG_GODS_CHARACTER_H
#define MEN_AMONG_GODS_CHARACTER_H

#include <cstdint>

#include <json/json.h>

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

  Json::Value      toJson() const;
  static character fromJson( const Json::Value& json );

  void setTotalExperienceFromSkillsAndAttributes();
};
#pragma pack( pop )
static_assert( sizeof( character ) == 3605 );

#endif