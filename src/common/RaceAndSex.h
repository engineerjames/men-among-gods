#ifndef MEN_AMONG_GODS_RACE_AND_SEX_H
#define MEN_AMONG_GODS_RACE_AND_SEX_H

#include <tuple>

#include "Logger.h"

namespace MenAmongGods
{
enum struct Sex
{
  Male,
  Female
};

enum struct Race
{
  Templar,
  Mercenary,
  Harakim,
  Seyan,
  God,
  ArchTemplar,
  ArchHarakim,
  Sorceror,
  Warrior
};

inline std::tuple< MenAmongGods::Race, MenAmongGods::Sex > getRaceAndSexFromInt( int raceAndSex )
{
  switch ( raceAndSex )
  {
  case 3:
    return std::make_tuple( MenAmongGods::Race::Templar, MenAmongGods::Sex::Male );
  case 2:
    return std::make_tuple( MenAmongGods::Race::Mercenary, MenAmongGods::Sex::Male );
  case 4:
    return std::make_tuple( MenAmongGods::Race::Harakim, MenAmongGods::Sex::Male );
  case 13:
    return std::make_tuple( MenAmongGods::Race::Seyan, MenAmongGods::Sex::Male );
  case 543:
    return std::make_tuple( MenAmongGods::Race::God, MenAmongGods::Sex::Male );
  case 544:
    return std::make_tuple( MenAmongGods::Race::ArchTemplar, MenAmongGods::Sex::Male );
  case 545:
    return std::make_tuple( MenAmongGods::Race::ArchHarakim, MenAmongGods::Sex::Male );
  case 546:
    return std::make_tuple( MenAmongGods::Race::Sorceror, MenAmongGods::Sex::Male );
  case 547:
    return std::make_tuple( MenAmongGods::Race::Warrior, MenAmongGods::Sex::Male );
  case 77:
    return std::make_tuple( MenAmongGods::Race::Templar, MenAmongGods::Sex::Female );
  case 76:
    return std::make_tuple( MenAmongGods::Race::Mercenary, MenAmongGods::Sex::Female );
  case 78:
    return std::make_tuple( MenAmongGods::Race::Harakim, MenAmongGods::Sex::Female );
  case 79:
    return std::make_tuple( MenAmongGods::Race::Seyan, MenAmongGods::Sex::Female );
  case 548:
    return std::make_tuple( MenAmongGods::Race::God, MenAmongGods::Sex::Female );
  case 549:
    return std::make_tuple( MenAmongGods::Race::ArchTemplar, MenAmongGods::Sex::Female );
  case 550:
    return std::make_tuple( MenAmongGods::Race::ArchHarakim, MenAmongGods::Sex::Female );
  case 551:
    return std::make_tuple( MenAmongGods::Race::Sorceror, MenAmongGods::Sex::Female );
  case 552:
    return std::make_tuple( MenAmongGods::Race::Warrior, MenAmongGods::Sex::Female );
  default:
    return std::make_tuple( MenAmongGods::Race::Templar, MenAmongGods::Sex::Male );
  }
}

inline int getOkeyRaceValue( MenAmongGods::Race race, MenAmongGods::Sex sex )
{
  if ( sex == MenAmongGods::Sex::Male )
  {
    switch ( race )
    {
    case MenAmongGods::Race::Templar:
      return 3;
    case MenAmongGods::Race::Mercenary:
      return 2;
    case MenAmongGods::Race::Harakim:
      return 4;
    case MenAmongGods::Race::Seyan:
      return 13;
    case MenAmongGods::Race::God:
      return 543;
    case MenAmongGods::Race::ArchTemplar:
      return 544;
    case MenAmongGods::Race::ArchHarakim:
      return 545;
    case MenAmongGods::Race::Sorceror:
      return 546;
    case MenAmongGods::Race::Warrior:
      return 547;

    default:
      LOG_ERROR( "Invalid race and sex combination for male." );
      break;
    }
  }
  else // Female
  {
    switch ( race )
    {
    case MenAmongGods::Race::Templar:
      return 77;
    case MenAmongGods::Race::Mercenary:
      return 76;
    case MenAmongGods::Race::Harakim:
      return 78;
    case MenAmongGods::Race::Seyan:
      return 79;
    case MenAmongGods::Race::God:
      return 548;
    case MenAmongGods::Race::ArchTemplar:
      return 549;
    case MenAmongGods::Race::ArchHarakim:
      return 550;
    case MenAmongGods::Race::Sorceror:
      return 551;
    case MenAmongGods::Race::Warrior:
      return 552;

    default:
      LOG_ERROR( "Invalid race and sex combination for female." );
      break;
    }
  }

  return -1;
}

} // namespace MenAmongGods

#endif