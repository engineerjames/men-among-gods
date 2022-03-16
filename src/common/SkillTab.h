#ifndef MEN_AMONG_GODS_SKILL_TAB_H
#define MEN_AMONG_GODS_SKILL_TAB_H

static constexpr const int SKILLTAB_SIZE = 50;

static const constexpr int AT_BRAVE = 0;
static const constexpr int AT_WILL  = 1;
static const constexpr int AT_INT   = 2;
static const constexpr int AT_AGIL  = 3;
static const constexpr int AT_STREN = 4;

struct skilltab
{
  int  nr;
  char sortkey;
  char name[ 40 ];
  char desc[ 200 ];

  int attrib[ 3 ];
};

extern const skilltab static_skilltab[SKILLTAB_SIZE];

#endif
