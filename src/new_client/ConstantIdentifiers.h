#ifndef CONSTANT_IDENTIFIERS_H
#define CONSTANT_IDENTIFIERS_H

#include <cstddef>
#include <string>

// Based heavily off of common.h
static const std::string   MNAME      = "Men Among Gods";
static const std::string   MHELP      = "http://mercaston.dnsalias.net/help.html";
static const std::string   MNEWS      = "http://mercaston.dnsalias.net/news.html";
static const std::string   MHOST      = "ec2-3-90-219-226.compute-1.amazonaws.com";
static const constexpr int MHOST_PORT = 5555;

static const constexpr int AT_BRAVE = 0;
static const constexpr int AT_WILL  = 1;
static const constexpr int AT_INT   = 2;
static const constexpr int AT_AGIL  = 3;
static const constexpr int AT_STREN = 4;

static const constexpr int   FONT_SIZE      = 10;
static const constexpr float LETTER_SPACING = 1.0f;

static const constexpr int MAX_SKILLS     = 50;
static const constexpr int MAX_ATTRIBUTES = 5;

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

static const constexpr unsigned int INJURED  = 1u << 0;
static const constexpr unsigned int INJURED1 = 1u << 1;
static const constexpr unsigned int INJURED2 = 1u << 2;
static const constexpr unsigned int STONED   = 1u << 3;
static const constexpr unsigned int INFRARED = 1u << 4;
static const constexpr unsigned int UWATER   = 1u << 5;
static const constexpr unsigned int ISUSABLE = 1u << 7;
static const constexpr unsigned int ISITEM   = 1u << 8;
static const constexpr unsigned int ISCHAR   = 1u << 9;
static const constexpr unsigned int INVIS    = 1u << 10;
static const constexpr unsigned int STUNNED  = 1u << 11;

static const constexpr unsigned int TOMB   = ( ( 1u << 12 ) | ( 1u << 13 ) | ( 1u << 14 ) | ( 1u << 15 ) | ( 1u << 16 ) );
static const constexpr unsigned int TOMB1  = ( 1u << 12 );
static const constexpr unsigned int DEATH  = ( ( 1u << 17 ) | ( 1u << 18 ) | ( 1u << 19 ) | ( 1u << 20 ) | ( 1u << 21 ) );
static const constexpr unsigned int DEATH1 = ( 1u << 17 );

static const constexpr unsigned int EMAGIC  = ( ( 1U << 22 ) | ( 1U << 23 ) | ( 1U << 24 ) );
static const constexpr unsigned int EMAGIC1 = ( 1U << 22 );
static const constexpr unsigned int GMAGIC  = ( ( 1U << 25 ) | ( 1U << 26 ) | ( 1U << 27 ) );
static const constexpr unsigned int GMAGIC1 = ( 1U << 25 );
static const constexpr unsigned int CMAGIC  = ( ( 1U << 28 ) | ( 1U << 29 ) | ( 1U << 30 ) );
static const constexpr unsigned int CMAGIC1 = ( 1U << 28 );

static const constexpr unsigned int MF_MOVEBLOCK  = 1U << 0;
static const constexpr unsigned int MF_SIGHTBLOCK = 1U << 1;
static const constexpr unsigned int MF_INDOORS    = 1U << 2;
static const constexpr unsigned int MF_UWATER     = 1U << 3;
static const constexpr unsigned int MF_NOLAG      = 1U << 4;
static const constexpr unsigned int MF_NOMONST    = 1U << 5;
static const constexpr unsigned int MF_BANK       = 1U << 6;
static const constexpr unsigned int MF_TAVERN     = 1U << 7;
static const constexpr unsigned int MF_NOMAGIC    = 1U << 8;
static const constexpr unsigned int MF_DEATHTRAP  = 1U << 9;

static const constexpr unsigned int MF_ARENA = 1U << 11;

static const constexpr unsigned int MF_NOEXPIRE = 1U << 13;

static const constexpr unsigned int HL_BUTTONBOX = 1;
static const constexpr unsigned int HL_STATBOX   = 2;
static const constexpr unsigned int HL_BACKPACK  = 3;
static const constexpr unsigned int HL_EQUIPMENT = 4;
static const constexpr unsigned int HL_SPELLBOX  = 5;
static const constexpr unsigned int HL_CITEM     = 6;
static const constexpr unsigned int HL_MONEY     = 7;
static const constexpr unsigned int HL_MAP       = 8;
static const constexpr unsigned int HL_SHOP      = 9;
static const constexpr unsigned int HL_STATBOX2  = 10;

static const constexpr unsigned int SPR_INVISIBLE       = 0;
static const constexpr unsigned int SPR_E1              = 1;
static const constexpr unsigned int SPR_E2              = 2;
static const constexpr unsigned int SPR_E3              = 3;
static const constexpr unsigned int SPR_E4              = 4;
static const constexpr unsigned int SPR_INV_MAP_PTR     = 5;
static const constexpr unsigned int SPR_MAP_PTR         = 6;
static const constexpr unsigned int SPR_FIGHT_PTR       = 7;
static const constexpr unsigned int SPR_INV_FIGHT_PTR   = 8;
static const constexpr unsigned int SPR_TAKE_PTR        = 9;
static const constexpr unsigned int SPR_INV_TAKE_PTR    = 10;
static const constexpr unsigned int SPR_INVALID_PTR     = 11;
static const constexpr unsigned int SPR_MISSION_SELECT  = 12; // fills 8 slots
static const constexpr unsigned int SPR_FIGHT_INT       = 20; // fills 48 slots
static const constexpr unsigned int SPR_INV_FIGHT_INT   = 68; // fills 24 slots
static const constexpr unsigned int SPR_LIGHT1          = 92;
static const constexpr unsigned int SPR_LIGHT2          = 93;
static const constexpr unsigned int SPR_LIGHT3          = 94;
static const constexpr unsigned int SPR_LIGHT4          = 95;
static const constexpr unsigned int SPR_LIGHT5          = 96;
static const constexpr unsigned int SPR_LIGHT6          = 97;
static const constexpr unsigned int SPR_EXIT            = 98;
static const constexpr unsigned int SPR_WALL_LB         = 99;  // fills 2 slots
static const constexpr unsigned int SPR_WALL_RB         = 101; // fills 2 slots
static const constexpr unsigned int SPR_WALL_LT         = 103; // fills 2 slots
static const constexpr unsigned int SPR_WALL_RT         = 105; // fills 2 slots
static const constexpr unsigned int SPR_WALL_VERT       = 107;
static const constexpr unsigned int SPR_WALL_HORIZ      = 108; // fills 2 slots
static const constexpr unsigned int SPR_DUNGEON_INT     = 110; // fills 48 slots
static const constexpr unsigned int SPR_INV_DUNGEON_INT = 158; // fills 24 slots
static const constexpr unsigned int SPR_INVENTORY_INT   = 182; // fills 36 slots
static const constexpr unsigned int SPR_MISSION_INT     = 218; // fills 48 slots
static const constexpr unsigned int SPR_INV_MISSION_INT = 266; // fills 24 slots
static const constexpr unsigned int SPR_STAT_INT        = 290; // fills 120 slots
static const constexpr unsigned int SPR_RANK0           = 410; // fills 8 slots
static const constexpr unsigned int SPR_RANK1           = 418; // fills 8 slots
static const constexpr unsigned int SPR_RANK2           = 426; // fills 8 slots
static const constexpr unsigned int SPR_RANK3           = 434; // fills 8 slots
static const constexpr unsigned int SPR_RANK4           = 442; // fills 8 slots
static const constexpr unsigned int SPR_RANK5           = 450; // fills 8 slots
static const constexpr unsigned int SPR_RANK6           = 458; // fills 8 slots
static const constexpr unsigned int SPR_RANK7           = 466; // fills 8 slots
static const constexpr unsigned int SPR_RANK8           = 474; // fills 8 slots
static const constexpr unsigned int SPR_RANK9           = 482; // fills 8 slots
static const constexpr unsigned int SPR_RANK10          = 490; // fills 8 slots
static const constexpr unsigned int SPR_RANK11          = 498; // fills 8 slots
static const constexpr unsigned int SPR_RANK12          = 506; // fills 8 slots
static const constexpr unsigned int SPR_RANK13          = 514; // fills 8 slots
static const constexpr unsigned int SPR_RANK14          = 522; // fills 8 slots
static const constexpr unsigned int SPR_RANK15          = 530; // fills 8 slots
static const constexpr unsigned int SPR_RANK16          = 538; // fills 8 slots
static const constexpr unsigned int SPR_RANK17          = 546; // fills 8 slots
static const constexpr unsigned int SPR_RANK18          = 554; // fills 8 slots
static const constexpr unsigned int SPR_RANK19          = 562; // fills 8 slots
static const constexpr unsigned int SPR_RANK20          = 570; // fills 8 slots
static const constexpr unsigned int SPR_SHOP_INT        = 578; // fills 48 slots
static const constexpr unsigned int SPR_INV_SHOP_INT    = 626; // fills 24 slots
static const constexpr unsigned int SPR_BUTTONBOX3      = 660; // fills 2 slots

static const constexpr unsigned int SPR_FONT     = 700; // fills 16 slots
static const constexpr unsigned int SPR_LOOK_INT = 716; // fills 120 slots

static const constexpr unsigned int SPR_EMPTY         = 999;
static const constexpr unsigned int SPR_TORCH3        = 1000;
static const constexpr unsigned int SPR_GROUND2       = 1002;
static const constexpr unsigned int SPR_HELMET        = 1003;
static const constexpr unsigned int SPR_BODY_ARMOR    = 1004;
static const constexpr unsigned int SPR_LEG_ARMOR     = 1005;
static const constexpr unsigned int SPR_SWORD         = 1006;
static const constexpr unsigned int SPR_DAGGER        = 1007;
static const constexpr unsigned int SPR_GROUND1       = 1008;
static const constexpr unsigned int SPR_CHEST_KEY     = 1009;
static const constexpr unsigned int SPR_STONE_GROUND1 = 1010;
static const constexpr unsigned int SPR_TORCH1        = 1011;
static const constexpr unsigned int SPR_PACKET0       = 1012;
static const constexpr unsigned int SPR_PACKET1       = 1013;
static const constexpr unsigned int SPR_PACKET2       = 1014;
static const constexpr unsigned int SPR_PACKET3       = 1015;
static const constexpr unsigned int SPR_PACKET4       = 1016;
static const constexpr unsigned int SPR_PACKET5       = 1017;
static const constexpr unsigned int SPR_PACKET6       = 1018;
static const constexpr unsigned int SPR_PACKET7       = 1019;
static const constexpr unsigned int SPR_PACKET8       = 1020;
static const constexpr unsigned int SPR_PACKET9       = 1021;
static const constexpr unsigned int SPR_PACKET_OVR    = 1022;
static const constexpr unsigned int SPR_PACKET_UDR    = 1023;
static const constexpr unsigned int SPR_PACKET_BRAKES = 1024;
static const constexpr unsigned int SPR_INT_BOX       = 1025;
static const constexpr unsigned int SPR_TORCH2        = 1026; // fills eight slots;

static const constexpr unsigned int SPR_NEWBIE = 2048;
static const constexpr unsigned int SPR_CHAR0  = 2048; // fills 256 slots
static const constexpr unsigned int SPR_CHAR1  = 2048; // fills 256 slots

static const constexpr unsigned int DR_IDLE        = 0;
static const constexpr unsigned int DR_DROP        = 1;
static const constexpr unsigned int DR_PICKUP      = 2;
static const constexpr unsigned int DR_GIVE        = 3;
static const constexpr unsigned int DR_USE         = 4;
static const constexpr unsigned int DR_BOW         = 5;
static const constexpr unsigned int DR_WAVE        = 6;
static const constexpr unsigned int DR_TURN        = 7;
static const constexpr unsigned int DR_SINGLEBUILD = 8;
static const constexpr unsigned int DR_AREABUILD1  = 9;
static const constexpr unsigned int DR_AREABUILD2  = 10;

// wear positions
static const constexpr unsigned int WN_HEAD  = 0;
static const constexpr unsigned int WN_NECK  = 1;
static const constexpr unsigned int WN_BODY  = 2;
static const constexpr unsigned int WN_ARMS  = 3;
static const constexpr unsigned int WN_BELT  = 4;
static const constexpr unsigned int WN_LEGS  = 5;
static const constexpr unsigned int WN_FEET  = 6;
static const constexpr unsigned int WN_LHAND = 7; // shield
static const constexpr unsigned int WN_RHAND = 8; // weapon
static const constexpr unsigned int WN_CLOAK = 9;
static const constexpr unsigned int WN_LRING = 10;
static const constexpr unsigned int WN_RRING = 11;

#endif // CONSTANT_IDENTIFIERS_H