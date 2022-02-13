#include "PlayerData.h"

#include <cstring>
#include <fstream>

#include <boost/archive/text_iarchive.hpp>

#include "ConstantIdentifiers.h"
#include "Logger.h"

namespace
{

static constexpr const std::size_t SKILLTAB_SIZE = 50;

int points2rank( int v )
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

static const std::array< const char*, 24 > rankToString = { "Private",
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

// clang-format off
// NOLINTNEXTLINE 
skilltab static_skilltab[SKILLTAB_SIZE]={
	{0,     'C',    "Hand to Hand", "Fighting without weapons.",                    {AT_BRAVE,AT_AGIL,AT_STREN}},
	{1,     'C',    "Karate",       "Fighting without weapons and doing damage.",   {AT_BRAVE,AT_AGIL,AT_STREN}},
	{2,     'C',    "Dagger",       "Fighting with daggers or similiar weapons.",   {AT_BRAVE,AT_AGIL,AT_INT}},
	{3,     'C',    "Sword",        "Fighting with swords or similiar weapons.",    {AT_BRAVE,AT_AGIL,AT_STREN}},
	{4,     'C',    "Axe",          "Fighting with axes or similiar weapons.",      {AT_BRAVE,AT_STREN,AT_STREN}},
	{5,     'C',    "Staff",        "Fighting with staffs or similiar weapons.",    {AT_AGIL,AT_STREN,AT_STREN}},
	{6,     'C',    "Two-Handed",   "Fighting with two-handed weapons.",            {AT_AGIL,AT_STREN,AT_STREN}},

	{7,     'G',    "Lock-Picking", "Opening doors without keys.",                  {AT_INT,AT_WILL,AT_AGIL}},
	{8,     'G',    "Stealth",      "Moving without being seen or heard.",          {AT_INT,AT_WILL,AT_AGIL}},
	{9,     'G',    "Perception",   "Seeing and hearing.",                          {AT_INT,AT_WILL,AT_AGIL}},

	{10,    'M',    "Swimming",     "Moving through water without drowning.",       {AT_INT,AT_WILL,AT_AGIL}},
	{11,    'R',    "Magic Shield", "Spell: Create a magic shield (Cost: 25 Mana).",  {AT_BRAVE,AT_INT,AT_WILL}},

	{12,    'G',    "Bartering",    "Getting good prices from merchants.",          {AT_BRAVE,AT_INT,AT_WILL}},
	{13,    'G',    "Repair",       "Repairing items.",                             {AT_INT,AT_WILL,AT_AGIL}},

	{14,    'R',    "Light",        "Spell: Create light (Cost: 5 Mana).",           {AT_BRAVE,AT_INT,AT_WILL}},
	{15,    'R',    "Recall",       "Spell: Teleport to temple (Cost: 15 Mana).",    {AT_BRAVE,AT_INT,AT_WILL}},
	{16,    'R',    "Guardian Angel","Spell: Avoid loss of HPs and items on death.", {AT_BRAVE,AT_INT,AT_WILL}},
	{17,    'R',    "Protection",   "Spell: Enhance Armor of target (Cost: 15 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{18,    'R',    "Enhance Weapon","Spell: Enhance Weapon of target (Cost: 15 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{19,    'R',    "Stun",         "Spell: Make target motionless (Cost: 20 Mana).",   {AT_BRAVE,AT_INT,AT_WILL}},
	{20,    'R',    "Curse",        "Spell: Decrease attributes of target (Cost: 35 Mana).",  {AT_BRAVE,AT_INT,AT_WILL}},
	{21,    'R',    "Bless",        "Spell: Increase attributes of target (Cost: 35 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{22,    'R',    "Identify",     "Spell: Read stats of item/character. (Cost: 25 Mana)",   {AT_BRAVE,AT_INT,AT_WILL}},

	{23,    'G',    "Resistance",   "Resist against magic.",                        {AT_INT,AT_WILL,AT_STREN}},

	{24,    'R',    "Blast",        "Spell: Inflict injuries to target (Cost: varies).", {AT_INT,AT_WILL,AT_STREN}},
	{25,    'R',    "Dispel Magic", "Spell: Removes curse magic from target (Cost: 25 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},

	{26,    'R',    "Heal",         "Spell: Heal injuries (Cost: 25 Mana).",         {AT_BRAVE,AT_INT,AT_WILL}},
	{27,    'R',    "Ghost Companion","Spell: Create a ghost to attack an enemy.",    {AT_BRAVE,AT_INT,AT_WILL}},

	{28,    'B',    "Regenerate",   "Regenerate Hitpoints faster.",                 {AT_STREN,AT_STREN,AT_STREN}},
	{29,    'B',    "Rest",         "Regenerate Endurance faster.",                 {AT_AGIL,AT_AGIL,AT_AGIL}},
	{30,    'B',    "Meditate",     "Regenerate Mana faster.",                      {AT_INT,AT_WILL,AT_WILL}},

	{31,    'G',    "Sense Magic",  "Find out who casts what at you.",              {AT_BRAVE,AT_INT,AT_WILL}},
	{32,    'G',    "Immunity",     "Partial immunity against negative magic.",     {AT_BRAVE,AT_AGIL,AT_STREN}},
	{33,    'G',    "Surround Hit", "Hit all your enemies at once.",                {AT_BRAVE,AT_AGIL,AT_STREN}},
	{34,    'G',    "Concentrate",  "Reduces mana cost for all spells.",            {AT_WILL,AT_WILL,AT_WILL}},
	{35,    'G',    "Warcry",       "Frighten all enemies in hearing distance.",    {AT_BRAVE,AT_BRAVE,AT_STREN}},

	{36,   'Z',   "", "", {0,0,0,}},
	{37,   'Z',   "", "", {0,0,0,}},
	{38,   'Z',   "", "", {0,0,0,}},
	{39,   'Z',   "", "", {0,0,0,}},

	{40,   'Z',   "", "", {0,0,0,}},
	{41,   'Z',   "", "", {0,0,0,}},
	{42,   'Z',   "", "", {0,0,0,}},
	{43,   'Z',   "", "", {0,0,0,}},
	{44,   'Z',   "", "", {0,0,0,}},
	{45,   'Z',   "", "", {0,0,0,}},
	{46,   'Z',   "", "", {0,0,0,}},
	{47,   'Z',   "", "", {0,0,0,}},
	{48,   'Z',   "", "", {0,0,0,}},
	{49,   'Z',   "", "", {0,0,0,}}};
// clang-format on

int getOkeyRaceValue( MenAmongGods::Race race, MenAmongGods::Sex sex )
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

} // namespace

// NOLINTNEXTLINE
std::map< unsigned short, looks > PlayerData::lookMap_ {};

// NOLINTNEXTLINE
int PlayerData::lookAt_ {};

PlayerData::PlayerData()
    : playerInfo_()
    , playerDataHasChanged_( true ) // Temporarily default to true
    , clientSidePlayerInfo_()
    , okey_()
    , skillsList_( &static_skilltab[ 0 ] )
    , look_()
    , password_()
    , messages_()
{
  for ( unsigned int i = 0; i < SKILLTAB_SIZE; ++i )
  {
    skillsList_[ i ].attrib[ 0 ] = 1;
  }

  setClientShouldShowNames( true );
  setClientShouldShowPercentHealth( true );
}

int PlayerData::getMode() const
{
  return clientSidePlayerInfo_.mode;
}

std::string PlayerData::getRankString() const
{
  int         rank       = points2rank( clientSidePlayerInfo_.points_tot );
  std::string rankString = rankToString[ rank ];

  return rankString;
}

int PlayerData::getRank() const
{
  return points2rank( clientSidePlayerInfo_.points_tot );
}

void PlayerData::setMode( int newMode )
{
  clientSidePlayerInfo_.mode = newMode;
}

std::string PlayerData::lookup( int nr, unsigned short id ) const
{
  static std::array< char, 40 > buf {};

  if ( id && id != lookMap_[ nr ].id )
  {
    lookMap_[ nr ].known     = 0;
    lookMap_[ nr ].name[ 0 ] = 0;
    lookMap_[ nr ].proz      = 0;
    lookMap_[ nr ].id        = id;
  }

  if ( ! lookMap_[ nr ].known )
  {
    lookAt_ = nr;
  }

  if ( ! id )
  {
    return lookMap_[ nr ].name;
  }

  if ( clientShouldShowNames() && clientShouldShowPercentHealth() )
  {
    if ( lookMap_[ nr ].proz )
    {
      sprintf( buf.data(), "%s %d%%", lookMap_[ nr ].name, lookMap_[ nr ].proz );
      return buf.data();
    }
    else
    {
      return lookMap_[ nr ].name;
    }
  }
  else if ( clientShouldShowNames() )
  {
    return lookMap_[ nr ].name;
  }
  else if ( clientShouldShowPercentHealth() )
  {
    if ( lookMap_[ nr ].proz )
    {
      sprintf( buf.data(), "%d%%", lookMap_[ nr ].proz );
      return buf.data();
    }
    else
    {
      return "";
    }
  }
  else
  {
    return "";
  }
}

// Usage like set_look_proz(map[m].ch_nr,map[m].ch_id,map[m].ch_proz);
void PlayerData::set_look_proz( unsigned short nr, unsigned short id, int proz ) const
{
  if ( id != lookMap_[ nr ].id )
  {
    lookMap_[ nr ].known     = 0;
    lookMap_[ nr ].name[ 0 ] = 0;
    lookMap_[ nr ].proz      = 0;
    lookMap_[ nr ].id        = id;
  }

  lookMap_[ nr ].proz = ( unsigned char ) proz;
}

void PlayerData::add_look( unsigned short nr, char* name, unsigned short id )
{
  LOG_DEBUG( "ADD_LOOK, nr=" << nr << ", name=" << name << ", id=" << id );

  if ( id != lookMap_[ nr ].id )
  {
    lookMap_[ nr ].known     = 0;
    lookMap_[ nr ].name[ 0 ] = 0;
    lookMap_[ nr ].proz      = 0;
  }

  std::strncpy( lookMap_[ nr ].name, name, 16 );
  lookMap_[ nr ].name[ 16 ] = 0;
  lookMap_[ nr ].known      = 1;
  lookMap_[ nr ].proz       = 0;
  lookMap_[ nr ].id         = id;
}

void PlayerData::setRaceAndSex( long unsigned int race )
{
  okey_.race = race;
}

bool PlayerData::hasPlayerDataChanged() const
{
  return playerDataHasChanged_;
}

int PlayerData::getPlayerDirection() const
{
  return clientSidePlayerInfo_.dir;
}

std::uint8_t PlayerData::areWallsHidden() const
{
  return playerInfo_.hide;
}

sf::Vector2i PlayerData::getGotoPosition() const
{
  return sf::Vector2i { clientSidePlayerInfo_.goto_x, clientSidePlayerInfo_.goto_y };
}

int PlayerData::getPlayerAction() const
{
  return clientSidePlayerInfo_.misc_action;
}

int PlayerData::getFirstTarget() const
{
  return clientSidePlayerInfo_.misc_target1;
}

int PlayerData::getSecondTarget() const
{
  return clientSidePlayerInfo_.misc_target2;
}

int PlayerData::clientShouldShowNames() const
{
  return playerInfo_.show_names;
}

int PlayerData::clientShouldShowPercentHealth() const
{
  return playerInfo_.show_proz;
}

void PlayerData::setClientShouldShowNames( bool shouldShowNames )
{
  playerInfo_.show_names = shouldShowNames ? 1 : 0;
}

void PlayerData::setClientShouldShowPercentHealth( bool shouldShowPercentHealth )
{
  playerInfo_.show_proz = shouldShowPercentHealth ? 1 : 0;
}

void PlayerData::setClientShouldHideWalls( bool shouldHideWalls )
{
  playerInfo_.hide = shouldHideWalls ? 1 : 0;
}

int PlayerData::getAttackTarget() const
{
  return clientSidePlayerInfo_.attack_cn;
}

const char* PlayerData::getPlayerName() const
{
  return playerInfo_.cname;
}

const char* PlayerData::getPlayerDescription() const
{
  return playerInfo_.desc;
}

void PlayerData::lock()
{
  ioMutex_.lock();
}

void PlayerData::unlock()
{
  ioMutex_.unlock();
}

void PlayerData::sortSkills()
{
  std::sort( skillsList_, skillsList_ + MAX_SKILLS,
             []( const skilltab& lhs, const skilltab& rhs )
             {
               // Begin server message processing implementation
               int m1 = lhs.nr;
               int m2 = rhs.nr;

               if ( m1 == 99 && m2 != 99 )
                 return true;
               if ( m2 == 99 && m1 != 99 )
                 return false;

               if ( lhs.sortkey > rhs.sortkey )
                 return true;
               if ( lhs.sortkey < rhs.sortkey )
                 return false;

               return strcmp( lhs.name, rhs.name ) > 0;
             } );
}

void PlayerData::addLogMessage( LogType type, const std::string& msg )
{
  messages_.emplace_back( type, msg );
}

std::vector< PlayerData::LogMessage > PlayerData::getAndClearLogMessages()
{
  // First, copy the vector that has all the new messages, then move it out of the
  // the function.  We then clear the internal data structure so we're only
  // sending the new messages each time.
  std::vector< PlayerData::LogMessage > messagesToReturn = messages_;
  messages_.clear();

  return messagesToReturn;
}

cplayer& PlayerData::getClientSidePlayerInfo()
{
  return clientSidePlayerInfo_;
}

const cplayer& PlayerData::getClientSidePlayerInfo() const
{
  return clientSidePlayerInfo_;
}

look& PlayerData::getLook()
{
  return look_;
}

void PlayerData::setName( std::string newName )
{
  std::strncpy( playerInfo_.cname, newName.c_str(), newName.length() );
}

void PlayerData::setPassword( std::string password )
{
  password_ = password;
}

std::string PlayerData::getPassword() const
{
  return password_;
}

void PlayerData::setPassword( long unsigned int pass1, long unsigned int pass2 )
{
  okey_.pass1 = pass1;
  okey_.pass2 = pass2;
}

void PlayerData::setDescription( std::string description )
{
  std::strncpy( playerInfo_.desc, description.c_str(), description.length() );
}

void PlayerData::setRaceAndSex( std::string race, std::string sex )
{
  MenAmongGods::Race raceEnum = MenAmongGods::Race::Mercenary;
  if ( race == "Harakim" )
  {
    raceEnum = MenAmongGods::Race::Harakim;
  }
  else if ( race == "Templar" )
  {
    raceEnum = MenAmongGods::Race::Templar;
  }
  else if ( race == "Mercenary" )
  {
    raceEnum = MenAmongGods::Race::Mercenary;
  }

  MenAmongGods::Sex sexEnum = MenAmongGods::Sex::Male;
  if ( sex == "Female" )
  {
    sexEnum = MenAmongGods::Sex::Female;
  }

  setRaceAndSex( getOkeyRaceValue( raceEnum, sexEnum ) );
}

int PlayerData::getRaceAndSex() const
{
  return okey_.race;
}

long unsigned int PlayerData::getUserNumber() const
{
  return okey_.usnr;
}

// NOLINTNEXTLINE
void PlayerData::setOkeyName( char ( &pdataName )[ 40 ] )
{
  std::strncpy( okey_.name, pdataName, sizeof( pdataName ) - 1 );
}

PlayerData::OkeyPasswordType PlayerData::getPasswordOkeyValues() const
{
  return std::make_tuple< long unsigned int, long unsigned int >( okey_.pass1, okey_.pass2 );
}

void PlayerData::setUserNumber( long unsigned int usnr )
{
  okey_.usnr = usnr;
}

void PlayerData::saveToFile() const
{
  std::ofstream                 playerFile( "player.archive" );
  boost::archive::text_oarchive playeroa { playerFile };

  if ( playerFile.is_open() )
  {
    playeroa << clientSidePlayerInfo_;
  }
  playerFile.close();
}

void PlayerData::loadFromFile( const std::string& filePath )
{
  std::ifstream                 playerFile( filePath );
  boost::archive::text_iarchive ia { playerFile };

  ia >> clientSidePlayerInfo_;

  playerFile.close();
}
