#ifndef MEN_AMONG_GODS_SKILLTAB_H
#define MEN_AMONG_GODS_SKILLTAB_H

#include "constants.h"

struct skilltab
{
  int  nr;
  char sortkey;
  char name[ 40 ];
  char desc[ 200 ];

  int attrib[ 3 ];
};

extern skilltab static_skilltab[SKILLTAB_SIZE];

#endif