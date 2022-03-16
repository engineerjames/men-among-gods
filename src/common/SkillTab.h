#ifndef MEN_AMONG_GODS_SKILL_TAB_H
#define MEN_AMONG_GODS_SKILL_TAB_H

#include <string>

static constexpr const int SKILLTAB_SIZE = 50;

static const constexpr int AT_BRAVE = 0;
static const constexpr int AT_WILL  = 1;
static const constexpr int AT_INT   = 2;
static const constexpr int AT_AGIL  = 3;
static const constexpr int AT_STREN = 4;

struct cplayer;

struct skilltab
{
  int  nr;
  char sortkey;
  char name[ 40 ];
  char desc[ 200 ];

  int attrib[ 3 ];
};

int hp_needed( int v, cplayer& pl );
int end_needed( int v, cplayer& pl );
int mana_needed( int v, cplayer& pl );
int attrib_needed( int n, int v, cplayer& pl );
int skill_needed( int n, int v, cplayer& pl );
int getSkillNumber( std::string skillName );
int getBaseAttributeModifier( const std::string& skillName );

extern const skilltab static_skilltab[SKILLTAB_SIZE];

#endif
