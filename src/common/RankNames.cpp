#include "RankNames.h"

const std::array< const char*, MenAmongGods::NUMBER_OF_RANKS > MenAmongGods::rankToStringShort = {
    " Pvt ", " PFC ", " LCp ", " Cpl ", " Sgt ", " SSg ", " MSg ", " 1Sg ", " SgM ", "2Lieu", "1Lieu", "Captn",
    "Major", "LtCol", "Colnl", "BrGen", "MaGen", "LtGen", "Genrl", "FDMAR", "KNIGT", "BARON", " EARL", "WARLD" };

const std::array< const char*, MenAmongGods::NUMBER_OF_RANKS > MenAmongGods::rankToString = { "Private",
                                                                                              "Private First Class",
                                                                                              "Lance Corporal",
                                                                                              "Corporal",
                                                                                              "Sergeant",
                                                                                              "Staff Sergeant",
                                                                                              "Master Sergeant",
                                                                                              "First Sergeant",
                                                                                              "Sergeant Major",
                                                                                              "Second Lieutenant",
                                                                                              "First Lieutenant",
                                                                                              "Captain",
                                                                                              "Major",
                                                                                              "Lieutenant Colonel",
                                                                                              "Colonel",
                                                                                              "Brigadier General",
                                                                                              "Major General",
                                                                                              "Lieutenant General",
                                                                                              "General",
                                                                                              "Field Marshal",
                                                                                              "Knight",
                                                                                              "Baron",
                                                                                              "Earl",
                                                                                              "Warlord" };

int MenAmongGods::points2rank( int v )
{
  if ( v < 50 )
    return 0;
  if ( v < 850 )
    return 1;
  if ( v < 4900 )
    return 2;
  if ( v < 17700 )
    return 3;
  if ( v < 48950 )
    return 4;
  if ( v < 113750 )
    return 5;
  if ( v < 233800 )
    return 6;
  if ( v < 438600 )
    return 7;
  if ( v < 766650 )
    return 8;
  if ( v < 1266650 )
    return 9;
  if ( v < 1998700 )
    return 10;
  if ( v < 3035500 )
    return 11;
  if ( v < 4463550 )
    return 12;
  if ( v < 6384350 )
    return 13;
  if ( v < 8915600 )
    return 14;
  if ( v < 12192400 )
    return 15;
  if ( v < 16368450 )
    return 16;
  if ( v < 21617250 )
    return 17;
  if ( v < 28133300 )
    return 18;
  if ( v < 36133300 )
    return 19;
  if ( v < 49014500 )
    return 20;
  if ( v < 63000600 )
    return 21;
  if ( v < 80977100 )
    return 22;

  return 23;
}