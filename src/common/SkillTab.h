#ifndef MEN_AMONG_GODS_SKILL_TAB_H
#define MEN_AMONG_GODS_SKILL_TAB_H

#include <string>

static constexpr const int MAX_SKILLS  = 50;
static constexpr const int MAX_ATTRIBUTES = 5;

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

int hp_needed( int v, int raceSpecificMaximum, int difficultyToRaise );
int end_needed( int v, int raceSpecificMaximum, int difficultyToRaise );
int mana_needed( int v, int raceSpecificMaximum, int difficultyToRaise );
int attrib_needed( int v, int raceSpecificMaximum, int difficultyToRaise );
int skill_needed( int v, int raceSpecificMaximum, int difficultyToRaise );
int getSkillNumber( std::string skillName );
int getBaseAttributeModifier( const std::string& skillName );

extern const skilltab static_skilltab[ MAX_SKILLS ];

#endif
