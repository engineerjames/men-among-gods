#ifndef MEN_AMONG_GODS_EQUIPMENT_CONSTANTS_H
#define MEN_AMONG_GODS_EQUIPMENT_CONSTANTS_H

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

#endif