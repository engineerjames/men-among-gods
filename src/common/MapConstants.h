#ifndef MEN_AMONG_GODS_MAP_CONSTANTS_H
#define MEN_AMONG_GODS_MAP_CONSTANTS_H

static const constexpr int TILEX = 34;
static const constexpr int TILEY = 34;
static const constexpr int MAPX  = TILEX;
static const constexpr int MAPY  = TILEY;
static const constexpr int YPOS  = 440;
static const constexpr int XPOS  = 0;

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
static const constexpr unsigned int TOMB     = ( ( 1u << 12 ) | ( 1u << 13 ) | ( 1u << 14 ) | ( 1u << 15 ) | ( 1u << 16 ) );
static const constexpr unsigned int TOMB1    = ( 1u << 12 );
static const constexpr unsigned int DEATH    = ( ( 1u << 17 ) | ( 1u << 18 ) | ( 1u << 19 ) | ( 1u << 20 ) | ( 1u << 21 ) );
static const constexpr unsigned int DEATH1   = ( 1u << 17 );
static const constexpr unsigned int EMAGIC   = ( ( 1U << 22 ) | ( 1U << 23 ) | ( 1U << 24 ) );
static const constexpr unsigned int EMAGIC1  = ( 1U << 22 );
static const constexpr unsigned int GMAGIC   = ( ( 1U << 25 ) | ( 1U << 26 ) | ( 1U << 27 ) );
static const constexpr unsigned int GMAGIC1  = ( 1U << 25 );
static const constexpr unsigned int CMAGIC   = ( ( 1U << 28 ) | ( 1U << 29 ) | ( 1U << 30 ) );
static const constexpr unsigned int CMAGIC1  = ( 1U << 28 );

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
static const constexpr unsigned int MF_ARENA      = 1U << 11;
static const constexpr unsigned int MF_NOEXPIRE   = 1U << 13;

#endif