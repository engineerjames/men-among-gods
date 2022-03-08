
#include <json/json.h>

#include <cstdint>

// TODO: Replace these with a game-wide  library
static constexpr const std::size_t SKILLTAB_SIZE = 50;

struct skilltab
{
  int  nr;
  char sortkey;
  char name[ 40 ];
  char desc[ 200 ];

  int attrib[ 3 ];
};

static const constexpr int AT_BRAVE = 0;
static const constexpr int AT_WILL  = 1;
static const constexpr int AT_INT   = 2;
static const constexpr int AT_AGIL  = 3;
static const constexpr int AT_STREN = 4;

// clang-format off
// NOLINTNEXTLINE
inline skilltab static_skilltab[SKILLTAB_SIZE]={
	{0,     'C',    "Hand to Hand", "Fighting without weapons.",                    {AT_BRAVE,AT_AGIL,AT_STREN}},
	{1,     'C',    "Karate",       "Fighting without weapons and doing damage.",   {AT_BRAVE,AT_AGIL,AT_STREN}},
	{2,     'C',    "Dagger",       "Fighting with daggers or similiar weapons.",   {AT_BRAVE,AT_AGIL,AT_INT}},
	{3,     'C',    "Sword",        "Fighting with swords or similiar weapons.",    {AT_BRAVE,AT_AGIL,AT_STREN}},
	{4,     'C',    "Axe",          "Fighting with axes or similiar weapons.",      {AT_BRAVE,AT_STREN,AT_STREN}},
	{5,     'C',    "Staff",        "Fighting with staffs or similiar weapons.",    {AT_AGIL,AT_STREN,AT_STREN}},
	{6,     'C',    "Two-Handed",   "Fighting with two-handed weapons.",            {AT_AGIL,AT_STREN,AT_STREN}},

	{7,     'G',    "Lock-Picking", "Opening doors without keys.",                  {AT_INT,AT_WILL,AT_AGIL}},
	{8,     'G',    "Stealth",      "Moving without being seen or heard.",          {AT_INT,AT_WILL,AT_AGIL}},
	{9,     'G',    "Perception",   "Seeing and hearing.",                          {AT_INT,AT_WILL,AT_AGIL}},

	{10,    'M',    "Swimming",     "Moving through water without drowning.",       {AT_INT,AT_WILL,AT_AGIL}},
	{11,    'R',    "Magic Shield", "Spell: Create a magic shield (Cost: 25 Mana).",  {AT_BRAVE,AT_INT,AT_WILL}},

	{12,    'G',    "Bartering",    "Getting good prices from merchants.",          {AT_BRAVE,AT_INT,AT_WILL}},
	{13,    'G',    "Repair",       "Repairing items.",                             {AT_INT,AT_WILL,AT_AGIL}},

	{14,    'R',    "Light",        "Spell: Create light (Cost: 5 Mana).",           {AT_BRAVE,AT_INT,AT_WILL}},
	{15,    'R',    "Recall",       "Spell: Teleport to temple (Cost: 15 Mana).",    {AT_BRAVE,AT_INT,AT_WILL}},
	{16,    'R',    "Guardian Angel","Spell: Avoid loss of HPs and items on death.", {AT_BRAVE,AT_INT,AT_WILL}},
	{17,    'R',    "Protection",   "Spell: Enhance Armor of target (Cost: 15 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{18,    'R',    "Enhance Weapon","Spell: Enhance Weapon of target (Cost: 15 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{19,    'R',    "Stun",         "Spell: Make target motionless (Cost: 20 Mana).",   {AT_BRAVE,AT_INT,AT_WILL}},
	{20,    'R',    "Curse",        "Spell: Decrease attributes of target (Cost: 35 Mana).",  {AT_BRAVE,AT_INT,AT_WILL}},
	{21,    'R',    "Bless",        "Spell: Increase attributes of target (Cost: 35 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{22,    'R',    "Identify",     "Spell: Read stats of item/character. (Cost: 25 Mana)",   {AT_BRAVE,AT_INT,AT_WILL}},

	{23,    'G',    "Resistance",   "Resist against magic.",                        {AT_INT,AT_WILL,AT_STREN}},

	{24,    'R',    "Blast",        "Spell: Inflict injuries to target (Cost: varies).", {AT_INT,AT_WILL,AT_STREN}},
	{25,    'R',    "Dispel Magic", "Spell: Removes curse magic from target (Cost: 25 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},

	{26,    'R',    "Heal",         "Spell: Heal injuries (Cost: 25 Mana).",         {AT_BRAVE,AT_INT,AT_WILL}},
	{27,    'R',    "Ghost Companion","Spell: Create a ghost to attack an enemy.",    {AT_BRAVE,AT_INT,AT_WILL}},

	{28,    'B',    "Regenerate",   "Regenerate Hitpoints faster.",                 {AT_STREN,AT_STREN,AT_STREN}},
	{29,    'B',    "Rest",         "Regenerate Endurance faster.",                 {AT_AGIL,AT_AGIL,AT_AGIL}},
	{30,    'B',    "Meditate",     "Regenerate Mana faster.",                      {AT_INT,AT_WILL,AT_WILL}},

	{31,    'G',    "Sense Magic",  "Find out who casts what at you.",              {AT_BRAVE,AT_INT,AT_WILL}},
	{32,    'G',    "Immunity",     "Partial immunity against negative magic.",     {AT_BRAVE,AT_AGIL,AT_STREN}},
	{33,    'G',    "Surround Hit", "Hit all your enemies at once.",                {AT_BRAVE,AT_AGIL,AT_STREN}},
	{34,    'G',    "Concentrate",  "Reduces mana cost for all spells.",            {AT_WILL,AT_WILL,AT_WILL}},
	{35,    'G',    "Warcry",       "Frighten all enemies in hearing distance.",    {AT_BRAVE,AT_BRAVE,AT_STREN}},

	{36,   'Z',   "", "", {0,0,0,}},
	{37,   'Z',   "", "", {0,0,0,}},
	{38,   'Z',   "", "", {0,0,0,}},
	{39,   'Z',   "", "", {0,0,0,}},

	{40,   'Z',   "", "", {0,0,0,}},
	{41,   'Z',   "", "", {0,0,0,}},
	{42,   'Z',   "", "", {0,0,0,}},
	{43,   'Z',   "", "", {0,0,0,}},
	{44,   'Z',   "", "", {0,0,0,}},
	{45,   'Z',   "", "", {0,0,0,}},
	{46,   'Z',   "", "", {0,0,0,}},
	{47,   'Z',   "", "", {0,0,0,}},
	{48,   'Z',   "", "", {0,0,0,}},
	{49,   'Z',   "", "", {0,0,0,}}};
// clang-format on

static const constexpr unsigned int KIN_MERCENARY   = ( 1u << 0 );
static const constexpr unsigned int KIN_SEYAN_DU    = ( 1u << 1 );
static const constexpr unsigned int KIN_PURPLE      = ( 1u << 2 );
static const constexpr unsigned int KIN_MONSTER     = ( 1u << 3 );
static const constexpr unsigned int KIN_TEMPLAR     = ( 1u << 4 );
static const constexpr unsigned int KIN_ARCHTEMPLAR = ( 1u << 5 );
static const constexpr unsigned int KIN_HARAKIM     = ( 1u << 6 );
static const constexpr unsigned int KIN_MALE        = ( 1u << 7 );
static const constexpr unsigned int KIN_FEMALE      = ( 1u << 8 );
static const constexpr unsigned int KIN_ARCHHARAKIM = ( 1u << 9 );
static const constexpr unsigned int KIN_WARRIOR     = ( 1u << 10 );
static const constexpr unsigned int KIN_SORCERER    = ( 1u << 11 );

static const constexpr unsigned long long CF_IMMORTAL    = ( 1ull << 0 );  // will not suffer any damage
static const constexpr unsigned long long CF_GOD         = ( 1ull << 1 );  // may issue #god commands
static const constexpr unsigned long long CF_CREATOR     = ( 1ull << 2 );  // may use #build
static const constexpr unsigned long long CF_BUILDMODE   = ( 1ull << 3 );  // does use #build
static const constexpr unsigned long long CF_RESPAWN     = ( 1ull << 4 );  // will respawn after death - not for players
static const constexpr unsigned long long CF_PLAYER      = ( 1ull << 5 );  // is a player
static const constexpr unsigned long long CF_NEWUSER     = ( 1ull << 6 );  // new account created. player may change name
static const constexpr unsigned long long CF_NOTELL      = ( 1ull << 8 );  // tell will only work on him if used by a god
static const constexpr unsigned long long CF_NOSHOUT     = ( 1ull << 9 );  // shout will only work in him if used by a god
static const constexpr unsigned long long CF_MERCHANT    = ( 1ull << 10 ); // will sell his inventory if looked at
static const constexpr unsigned long long CF_STAFF       = ( 1ull << 11 ); // member of the staff
static const constexpr unsigned long long CF_NOHPREG     = ( 1ull << 12 ); // no hp regeneration
static const constexpr unsigned long long CF_NOENDREG    = ( 1ull << 13 );
static const constexpr unsigned long long CF_NOMANAREG   = ( 1ull << 14 );
static const constexpr unsigned long long CF_INVISIBLE   = ( 1ull << 15 ); // character is completely invisible
static const constexpr unsigned long long CF_INFRARED    = ( 1ull << 16 ); // sees in the dark
static const constexpr unsigned long long CF_BODY        = ( 1ull << 17 ); // dead body
static const constexpr unsigned long long CF_NOSLEEP     = ( 1ull << 18 ); // stay awake all the time
static const constexpr unsigned long long CF_UNDEAD      = ( 1ull << 19 ); // is undead, can be killed with holy water
static const constexpr unsigned long long CF_NOMAGIC     = ( 1ull << 20 ); // no magic zone
static const constexpr unsigned long long CF_STONED      = ( 1ull << 21 ); // turned to stone due to lag
static const constexpr unsigned long long CF_USURP       = ( 1ull << 22 ); // NPC is being played by player
static const constexpr unsigned long long CF_IMP         = ( 1ull << 23 ); // may impersonate monsters
static const constexpr unsigned long long CF_SHUTUP      = ( 1ull << 24 ); // player is unable to talk till next day
static const constexpr unsigned long long CF_NODESC      = ( 1ull << 25 ); // player cannot change his description
static const constexpr unsigned long long CF_PROF        = ( 1ull << 26 ); // profiler listing
static const constexpr unsigned long long CF_SIMPLE      = ( 1ull << 27 ); // uses simple animation system (move, turn, 1 attack)
static const constexpr unsigned long long CF_KICKED      = ( 1ull << 28 ); // player got kicked, may not login again for a certain time
static const constexpr unsigned long long CF_NOLIST      = ( 1ull << 29 ); // dont list character in top ten
static const constexpr unsigned long long CF_NOWHO       = ( 1ull << 30 ); // don't list character in #WHO
static const constexpr unsigned long long CF_SPELLIGNORE = ( 1ull << 31 ); // ignore spells cast on me
static const constexpr unsigned long long CF_CCP =
    ( 1ull << 32 ); // Computer Controlled Player, does NOT log out and may have some extra logic
static const constexpr unsigned long long CF_SAFE       = ( 1ull << 33 ); // safety measures for gods
static const constexpr unsigned long long CF_NOSTAFF    = ( 1ull << 34 ); // #stell will only work if flag off
static const constexpr unsigned long long CF_POH        = ( 1ull << 35 ); // clan purples of honor
static const constexpr unsigned long long CF_POH_LEADER = ( 1ull << 36 ); // clan purples of honor
static const constexpr unsigned long long CF_THRALL     = ( 1ull << 37 ); // is enthralled NPC
static const constexpr unsigned long long CF_LABKEEPER  = ( 1ull << 38 ); // is labkeeper
static const constexpr unsigned long long CF_ISLOOTING  = ( 1ull << 39 ); // is currently looting a grave
static const constexpr unsigned long long CF_GOLDEN     = ( 1ull << 40 ); // is on "golden list" aka good player
static const constexpr unsigned long long CF_BLACK      = ( 1ull << 41 ); // is on "black list" aka bad player
static const constexpr unsigned long long CF_PASSWD     = ( 1ull << 42 ); // has passwd set
static const constexpr unsigned long long CF_UPDATE     = ( 1ull << 43 ); // client side update needed
static const constexpr unsigned long long CF_SAVEME     = ( 1ull << 44 ); // save this player to disk
static const constexpr unsigned long long CF_GREATERGOD = ( 1ull << 45 ); // greater god
static const constexpr unsigned long long CF_GREATERINV = ( 1ull << 46 ); // no one sees me, ever

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

    root[ "hp" ]   = Json::arrayValue;
    root[ "end" ]  = Json::arrayValue;
    root[ "mana" ] = Json::arrayValue;

    for ( int i = 0; i < 3; ++i )
    {
      root[ "hp" ][ i ]   = hp[ i ];
      root[ "end" ][ i ]  = end[ i ];
      root[ "mana" ][ i ] = mana[ i ];
    }

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

    root[ "future" ]  = future;
    root[ "future3" ] = Json::arrayValue;
    for ( int i = 0; i < 9; ++i )
    {
      root[ "future3" ][ i ] = future3[ i ];
    }

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
static_assert( sizeof( item ) == 634 );

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

    root[ "used" ]                              = used;
    root[ "name" ]                              = name;
    root[ "reference" ]                         = reference;
    root[ "description" ]                       = description;
    root[ "kindred" ]                           = kindred;
    root[ "player" ]                            = player;
    root[ "pass1" ]                             = pass1;
    root[ "pass2" ]                             = pass2;
    root[ "sprite" ]                            = sprite;
    root[ "sound" ]                             = sound;
    root[ "flags" ]                             = Json::objectValue;
    root[ "flags" ][ "immortal" ]               = static_cast< bool >( flags & CF_IMMORTAL );
    root[ "flags" ][ "god" ]                    = static_cast< bool >( flags & CF_GOD );
    root[ "flags" ][ "creator" ]                = static_cast< bool >( flags & CF_CREATOR );
    root[ "flags" ][ "build_mode" ]             = static_cast< bool >( flags & CF_BUILDMODE );
    root[ "flags" ][ "respawn" ]                = static_cast< bool >( flags & CF_RESPAWN );
    root[ "flags" ][ "player" ]                 = static_cast< bool >( flags & CF_PLAYER );
    root[ "flags" ][ "new_user" ]               = static_cast< bool >( flags & CF_NEWUSER );
    root[ "flags" ][ "no_tell" ]                = static_cast< bool >( flags & CF_NOTELL );
    root[ "flags" ][ "no_shout" ]               = static_cast< bool >( flags & CF_NOSHOUT );
    root[ "flags" ][ "merchant" ]               = static_cast< bool >( flags & CF_MERCHANT );
    root[ "flags" ][ "staff" ]                  = static_cast< bool >( flags & CF_STAFF );
    root[ "flags" ][ "no_hp_regen" ]            = static_cast< bool >( flags & CF_NOHPREG );
    root[ "flags" ][ "no_end_regen" ]           = static_cast< bool >( flags & CF_NOENDREG );
    root[ "flags" ][ "no_mana_regen" ]          = static_cast< bool >( flags & CF_NOMANAREG );
    root[ "flags" ][ "invisible" ]              = static_cast< bool >( flags & CF_INVISIBLE );
    root[ "flags" ][ "infrared" ]               = static_cast< bool >( flags & CF_INFRARED );
    root[ "flags" ][ "body" ]                   = static_cast< bool >( flags & CF_BODY );
    root[ "flags" ][ "no_sleep" ]               = static_cast< bool >( flags & CF_NOSLEEP );
    root[ "flags" ][ "undead" ]                 = static_cast< bool >( flags & CF_UNDEAD );
    root[ "flags" ][ "no_magic" ]               = static_cast< bool >( flags & CF_NOMAGIC );
    root[ "flags" ][ "stoned" ]                 = static_cast< bool >( flags & CF_STONED );
    root[ "flags" ][ "usurp" ]                  = static_cast< bool >( flags & CF_USURP );
    root[ "flags" ][ "imp" ]                    = static_cast< bool >( flags & CF_IMP );
    root[ "flags" ][ "shutup" ]                 = static_cast< bool >( flags & CF_SHUTUP );
    root[ "flags" ][ "no_description" ]         = static_cast< bool >( flags & CF_NODESC );
    root[ "flags" ][ "profiler" ]               = static_cast< bool >( flags & CF_PROF );
    root[ "flags" ][ "simple_anim" ]            = static_cast< bool >( flags & CF_SIMPLE );
    root[ "flags" ][ "kicked" ]                 = static_cast< bool >( flags & CF_KICKED );
    root[ "flags" ][ "no_list" ]                = static_cast< bool >( flags & CF_NOLIST );
    root[ "flags" ][ "no_who" ]                 = static_cast< bool >( flags & CF_NOWHO );
    root[ "flags" ][ "spell_ignore" ]           = static_cast< bool >( flags & CF_SPELLIGNORE );
    root[ "flags" ][ "computer_controlled" ]    = static_cast< bool >( flags & CF_CCP );
    root[ "flags" ][ "safe" ]                   = static_cast< bool >( flags & CF_SAFE );
    root[ "flags" ][ "no_staff" ]               = static_cast< bool >( flags & CF_NOSTAFF );
    root[ "flags" ][ "purple_of_honor" ]        = static_cast< bool >( flags & CF_POH );
    root[ "flags" ][ "purple_of_honor_leader" ] = static_cast< bool >( flags & CF_POH_LEADER );
    root[ "flags" ][ "thrall" ]                 = static_cast< bool >( flags & CF_THRALL );
    root[ "flags" ][ "lab_keeper" ]             = static_cast< bool >( flags & CF_LABKEEPER );
    root[ "flags" ][ "is_looting" ]             = static_cast< bool >( flags & CF_ISLOOTING );
    root[ "flags" ][ "golden" ]                 = static_cast< bool >( flags & CF_GOLDEN );
    root[ "flags" ][ "black" ]                  = static_cast< bool >( flags & CF_BLACK );
    root[ "flags" ][ "password" ]               = static_cast< bool >( flags & CF_PASSWD );
    root[ "flags" ][ "update" ]                 = static_cast< bool >( flags & CF_UPDATE );
    root[ "flags" ][ "save_me" ]                = static_cast< bool >( flags & CF_SAVEME );
    root[ "flags" ][ "greater_god" ]            = static_cast< bool >( flags & CF_GREATERGOD );
    root[ "flags" ][ "greater_invisibility" ]   = static_cast< bool >( flags & CF_GREATERINV );
    root[ "alignment" ]                         = alignment;
    root[ "temple_x" ]                          = temple_x;
    root[ "temple_y" ]                          = temple_y;
    root[ "tavern_x" ]                          = tavern_x;
    root[ "tavern_y" ]                          = tavern_y;
    root[ "temp" ]                              = temp;

    root[ "attributes" ]                        = Json::arrayValue;
    std::array< const char*, 5 > attributeNames = { "Braveness", "Willpower", "Intuition", "Agility", "Strength" };
    for ( int i = 0; i < 5; ++i )
    {
      Json::Value attributeRoot {};
      attributeRoot[ "name" ] = attributeNames[ i ];
      attributeRoot[ "data" ] = Json::arrayValue;
      for ( int j = 0; j < 6; ++j )
      {
        attributeRoot[ "data" ].append( attrib[ i ][ j ] );
      }

      attributeRoot[ "attributes" ].append( attributeRoot );
    }

    root[ "hp" ]   = Json::arrayValue;
    root[ "end" ]  = Json::arrayValue;
    root[ "mana" ] = Json::arrayValue;

    for ( int i = 0; i < 6; ++i )
    {
      root[ "hp" ][ i ]   = hp[ i ];
      root[ "end" ][ i ]  = end[ i ];
      root[ "mana" ][ i ] = mana[ i ];
    }

    root[ "skills" ] = Json::arrayValue;
    for ( int i = 0; i < 50; ++i )
    {
      Json::Value skillRoot {};
      skillRoot[ "name" ] = static_skilltab[ i ].name;
      skillRoot[ "data" ] = Json::arrayValue;
      for ( int j = 0; j < 6; ++j )
      {
        skillRoot[ "data" ].append( skill[ i ][ j ] );
      }

      root[ "skills" ].append( skillRoot );
    }

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

    root[ "item" ] = Json::arrayValue;
    for ( int i = 0; i < 40; ++i )
    {
      root[ "item" ][ i ] = item[ i ];
    }

    root[ "worn" ]  = Json::arrayValue;
    root[ "spell" ] = Json::arrayValue;
    for ( int i = 0; i < 20; ++i )
    {
      root[ "worn" ][ i ]  = worn[ i ];
      root[ "spell" ][ i ] = spell[ i ];
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

    root[ "future1" ] = Json::arrayValue;
    root[ "future2" ] = Json::arrayValue;
    root[ "depot" ]   = Json::arrayValue;
    root[ "future3" ] = Json::arrayValue;
    root[ "data" ]    = Json::arrayValue;
    root[ "text" ]    = Json::arrayValue;

    for ( int i = 0; i < 25; ++i )
    {
      root[ "future1" ][ i ] = future1[ i ];
    }

    for ( int i = 0; i < 49; ++i )
    {
      root[ "future2" ][ i ] = future2[ i ];
    }

    for ( int i = 0; i < 62; ++i )
    {
      root[ "depot" ][ i ] = depot[ i ];
    }

    for ( int i = 0; i < 12; ++i )
    {
      root[ "future3" ][ i ] = future3[ i ];
    }

    for ( int i = 0; i < 100; ++i )
    {
      root[ "data" ][ i ] = data[ i ];
    }

    for ( int i = 0; i < 10; ++i )
    {
      root[ "text" ][ i ] = std::string( text[ i ] );
    }

    root[ "sprite_override" ] = sprite_override;
    root[ "depot_cost" ]      = depot_cost;
    root[ "luck" ]            = luck;
    root[ "unreach" ]         = unreach;
    root[ "unreach_x" ]       = unreachx;
    root[ "unreach_y" ]       = unreachy;
    root[ "monsterClass" ]    = monsterClass;

    return root;
  }
};
#pragma pack( pop )
static_assert( sizeof( character ) == 3605 );
