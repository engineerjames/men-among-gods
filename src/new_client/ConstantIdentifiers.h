#ifndef CONSTANT_IDENTIFIERS_H
#define CONSTANT_IDENTIFIERS_H

#include <cstddef>
#include <string>

// Based heavily off of common.h
static const std::string   MNAME      = "Asguard";
static const std::string   MHELP      = "http://mercaston.dnsalias.net/help.html";
static const std::string   MNEWS      = "http://mercaston.dnsalias.net/news.html";
static const std::string   MHOST      = "127.0.0.1";
static const constexpr int MHOST_PORT = 5555;

static const constexpr int AT_BRAVE = 0;
static const constexpr int AT_WILL  = 1;
static const constexpr int AT_INT   = 2;
static const constexpr int AT_AGIL  = 3;
static const constexpr int AT_STREN = 4;

static const constexpr int          TILEX     = 34;
static const constexpr int          TILEY     = 34;
static const constexpr int          TICKS     = 18;
static const constexpr unsigned int VERSION   = 0x020E06;
static const constexpr int          MAXSPRITE = 2000 + ( 32 * 1024 );

static const constexpr int MODEX = 800;
static const constexpr int MODEY = 600;

static const constexpr int MAPX = TILEX;
static const constexpr int MAPY = TILEY;

static const constexpr int YPOS = 440;
static const constexpr int XPOS = 0;

// Should this be a float?
static const constexpr int          TICK     = ( 1000 / TICKS );
static const constexpr unsigned int HIGH_VAL = 1 << 30;

enum struct MOUSE_STATES
{
  MS_MOVE    = 0,
  MS_LB_DOWN = 1,
  MS_RB_DOWN = 2,
  MS_LB_UP   = 3,
  MS_RB_UP   = 4
};

static const constexpr int QSIZE = 8;

enum struct WEAR_POSITIONS
{
  WN_HEAD,
  WN_NECK,
  WN_BODY,
  WN_ARMS,
  WN_BELT,
  WN_LEGS,
  WN_FEET,
  WN_LHAND, // shield
  WN_RHAND, // weapon
  WN_CLOAK,
  WN_LRING,
  WN_RRING
};

enum struct PLACEMENT_BITS
{
  PL_HEAD    = 1,
  PL_NECK    = 2,
  PL_BODY    = 4,
  PL_ARMS    = 8,
  PL_BELT    = 32,
  PL_LEGS    = 64,
  PL_FEET    = 128,
  PL_WEAPON  = 256,
  PL_SHIELD  = 512,
  PL_CLOAK   = 1024,
  PL_TWOHAND = 2048,
  PL_RING    = 4096
};

#define DX_RIGHT 1
#define DX_LEFT 2
#define DX_UP 3
#define DX_DOWN 4

#define INJURED ( 1u << 0 )
#define INJURED1 ( 1u << 1 )
#define INJURED2 ( 1u << 2 )
#define STONED ( 1u << 3 )
#define INFRARED ( 1u << 4 )
#define UWATER ( 1u << 5 )

#define ISUSABLE ( 1u << 7 )
#define ISITEM ( 1u << 8 )
#define ISCHAR ( 1u << 9 )
#define INVIS ( 1u << 10 )
#define STUNNED ( 1u << 11 )

#define TOMB ( ( 1u << 12 ) | ( 1u << 13 ) | ( 1u << 14 ) | ( 1u << 15 ) | ( 1u << 16 ) )
#define TOMB1 ( 1u << 12 )
#define DEATH ( ( 1u << 17 ) | ( 1u << 18 ) | ( 1u << 19 ) | ( 1u << 20 ) | ( 1u << 21 ) )
#define DEATH1 ( 1u << 17 )

#define EMAGIC ( ( 1U << 22 ) | ( 1U << 23 ) | ( 1U << 24 ) )
#define EMAGIC1 ( 1U << 22 )
#define GMAGIC ( ( 1U << 25 ) | ( 1U << 26 ) | ( 1U << 27 ) )
#define GMAGIC1 ( 1U << 25 )
#define CMAGIC ( ( 1U << 28 ) | ( 1U << 29 ) | ( 1U << 30 ) )
#define CMAGIC1 ( 1U << 28 )

#define MF_MOVEBLOCK ( 1U << 0 )
#define MF_SIGHTBLOCK ( 1U << 1 )
#define MF_INDOORS ( 1U << 2 )
#define MF_UWATER ( 1U << 3 )
#define MF_NOLAG ( 1U << 4 )
#define MF_NOMONST ( 1U << 5 )
#define MF_BANK ( 1U << 6 )
#define MF_TAVERN ( 1U << 7 )
#define MF_NOMAGIC ( 1U << 8 )
#define MF_DEATHTRAP ( 1U << 9 )

#define MF_ARENA ( 1U << 11 )

#define MF_NOEXPIRE ( 1U << 13 )

#define SPR_INVISIBLE 0
#define SPR_E1 1
#define SPR_E2 2
#define SPR_E3 3
#define SPR_E4 4
#define SPR_INV_MAP_PTR 5
#define SPR_MAP_PTR 6
#define SPR_FIGHT_PTR 7
#define SPR_INV_FIGHT_PTR 8
#define SPR_TAKE_PTR 9
#define SPR_INV_TAKE_PTR 10
#define SPR_INVALID_PTR 11
#define SPR_MISSION_SELECT 12 // fills 8 slots
#define SPR_FIGHT_INT 20      // fills 48 slots
#define SPR_INV_FIGHT_INT 68  // fills 24 slots
#define SPR_LIGHT1 92
#define SPR_LIGHT2 93
#define SPR_LIGHT3 94
#define SPR_LIGHT4 95
#define SPR_LIGHT5 96
#define SPR_LIGHT6 97
#define SPR_EXIT 98
#define SPR_WALL_LB 99  // fills 2 slots
#define SPR_WALL_RB 101 // fills 2 slots
#define SPR_WALL_LT 103 // fills 2 slots
#define SPR_WALL_RT 105 // fills 2 slots
#define SPR_WALL_VERT 107
#define SPR_WALL_HORIZ 108      // fills 2 slots
#define SPR_DUNGEON_INT 110     // fills 48 slots
#define SPR_INV_DUNGEON_INT 158 // fills 24 slots
#define SPR_INVENTORY_INT 182   // fills 36 slots
#define SPR_MISSION_INT 218     // fills 48 slots
#define SPR_INV_MISSION_INT 266 // fills 24 slots
#define SPR_STAT_INT 290        // fills 120 slots
#define SPR_RANK0 410           // fills 8 slots
#define SPR_RANK1 418           // fills 8 slots
#define SPR_RANK2 426           // fills 8 slots
#define SPR_RANK3 434           // fills 8 slots
#define SPR_RANK4 442           // fills 8 slots
#define SPR_RANK5 450           // fills 8 slots
#define SPR_RANK6 458           // fills 8 slots
#define SPR_RANK7 466           // fills 8 slots
#define SPR_RANK8 474           // fills 8 slots
#define SPR_RANK9 482           // fills 8 slots
#define SPR_RANK10 490          // fills 8 slots
#define SPR_RANK11 498          // fills 8 slots
#define SPR_RANK12 506          // fills 8 slots
#define SPR_RANK13 514          // fills 8 slots
#define SPR_RANK14 522          // fills 8 slots
#define SPR_RANK15 530          // fills 8 slots
#define SPR_RANK16 538          // fills 8 slots
#define SPR_RANK17 546          // fills 8 slots
#define SPR_RANK18 554          // fills 8 slots
#define SPR_RANK19 562          // fills 8 slots
#define SPR_RANK20 570          // fills 8 slots
#define SPR_SHOP_INT 578        // fills 48 slots
#define SPR_INV_SHOP_INT 626    // fills 24 slots
#define SPR_BUTTONBOX3 660      // fills 2 slots

#define SPR_FONT 700     // fills 16 slots
#define SPR_LOOK_INT 716 // fills 120 slots

#define SPR_EMPTY 999
#define SPR_TORCH3 1000
#define SPR_GROUND2 1002
#define SPR_HELMET 1003
#define SPR_BODY_ARMOR 1004
#define SPR_LEG_ARMOR 1005
#define SPR_SWORD 1006
#define SPR_DAGGER 1007
#define SPR_GROUND1 1008
#define SPR_CHEST_KEY 1009
#define SPR_STONE_GROUND1 1010
#define SPR_TORCH1 1011
#define SPR_PACKET0 1012
#define SPR_PACKET1 1013
#define SPR_PACKET2 1014
#define SPR_PACKET3 1015
#define SPR_PACKET4 1016
#define SPR_PACKET5 1017
#define SPR_PACKET6 1018
#define SPR_PACKET7 1019
#define SPR_PACKET8 1020
#define SPR_PACKET9 1021
#define SPR_PACKET_OVR 1022
#define SPR_PACKET_UDR 1023
#define SPR_PACKET_BRAKES 1024
#define SPR_INT_BOX 1025
#define SPR_TORCH2 1026 // fills eight slots

#define SPR_NEWBIE 2048
#define SPR_CHAR0 2048 // fills 256 slots
#define SPR_CHAR1 2048 // fills 256 slots

#define DR_IDLE 0
#define DR_DROP 1
#define DR_PICKUP 2
#define DR_GIVE 3
#define DR_USE 4
#define DR_BOW 5
#define DR_WAVE 6
#define DR_TURN 7
#define DR_SINGLEBUILD 8
#define DR_AREABUILD1 9
#define DR_AREABUILD2 10

#endif // CONSTANT_IDENTIFIERS_H