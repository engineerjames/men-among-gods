#ifndef MEN_AMONG_GODS_CONSTANTS_H
#define MEN_AMONG_GODS_CONSTANTS_H

#include <cstdint>
#include <cstring>

static const constexpr unsigned int CLIENT_FRAME_LIMIT   = 60;
static const float                  LOOK_TIME_IN_SECONDS = 10.0f;

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

static const constexpr unsigned int SPR_EMPTY = 999;

#endif