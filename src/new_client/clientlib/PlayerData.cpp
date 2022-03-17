#include "PlayerData.h"

#include <cstring>
#include <fstream>
#include <iostream>

#include <json/json.h>

#include "ClientConfiguration.h"
#include "ClientTypes.h"
#include "ConstantIdentifiers.h"
#include "InventoryConstants.h"
#include "Logger.h"
#include "RankNames.h"
#include "ResourceLocations.h"
#include "RaceAndSex.h"

namespace
{

static const float LOOK_TIME_IN_SECONDS = 10.0f;

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
    , skillsList_()
    , look_()
    , password_()
    , messages_()
    , playerSprite_()
    , selectedCharacter_()
    , shouldShowLook_( false )
    , shouldShowShop_( false )
    , shop_()
    , unique1_()
    , unique2_()
{
  for ( int i = 0; i < MAX_SKILLS; ++i )
  {
    skillsList_[ i ] = static_skilltab[ i ];
  }

  setClientShouldShowNames( true );
  setClientShouldShowPercentHealth( true );
}

int PlayerData::getMode() const
{
  return clientSidePlayerInfo_.mode;
}

void PlayerData::setPlayerSprite( int spriteId )
{
  playerSprite_ = spriteId;
}

void PlayerData::setUnique1( int newValue )
{
  unique1_ = newValue;
}

void PlayerData::setUnique2( int newValue )
{
  unique2_ = newValue;
}

int PlayerData::getUnique1() const
{
  return unique1_;
}

int PlayerData::getUnique2() const
{
  return unique2_;
}

int PlayerData::getPlayerSprite() const
{
  return playerSprite_;
}

void PlayerData::setSelectedCharacter( int characterId )
{
  selectedCharacter_ = characterId;
}

int PlayerData::getSelectedCharacter() const
{
  return selectedCharacter_;
}

bool PlayerData::getShowLook() const
{
  return shouldShowLook_;
}

void PlayerData::setShowLook( bool shouldShowLook )
{
  shouldShowLook_ = shouldShowLook;
}

bool PlayerData::getShouldShowShop() const
{
  return shouldShowShop_;
}

void PlayerData::setShouldShowShop( bool shouldShowShop )
{
  shouldShowShop_ = shouldShowShop;
}

void PlayerData::setShopOnCurrentLook()
{
  shop_ = look_;
}

look PlayerData::getShop() const
{
  return shop_;
}

std::string PlayerData::getRankString() const
{
  int         rank       = points2rank( clientSidePlayerInfo_.points_tot );
  std::string rankString = MenAmongGods::rankToString[ rank ];

  return rankString;
}

int PlayerData::getItem( int index ) const
{
  if ( index < N_ITEMS && index >= 0 )
  {
    return clientSidePlayerInfo_.item[ index ];
  }
  else
  {
    LOG_ERROR( "Invalid item index: " << index );
    return 0;
  }
}

int PlayerData::getRank() const
{
  return points2rank( clientSidePlayerInfo_.points_tot );
}

void PlayerData::setMode( int newMode )
{
  clientSidePlayerInfo_.mode = newMode;
}

std::vector< int > PlayerData::getUnknownCharacterIds() const
{
  std::vector< int > unknownIds {};
  for ( const auto& [ key, val ] : lookMap_ )
  {
    if ( val.known == 0 )
    {
      unknownIds.push_back( key );
    }
  }

  return unknownIds;
}

char PlayerData::get_proz( int nr, unsigned short id ) const
{
  if ( id && lookMap_[ nr ].id != 0 )
  {
    return lookMap_[ nr ].proz;
  }
  else
  {
    return 127;
  }
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
  std::sort( std::begin( skillsList_ ), std::end( skillsList_ ),
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

void PlayerData::resetLookTimer()
{
  lookTimer_ = 0.0f;
}

void PlayerData::incrementLookTimer()
{
  lookTimer_ += ( 1.0f / static_cast< float >( MenAmongGods::ClientConfiguration::instance().frameLimit() ) );

  if ( lookTimer_ >= LOOK_TIME_IN_SECONDS )
  {
    lookTimer_ = 0.0f;
    setShowLook( false );
  }
}

void PlayerData::setName( std::string newName )
{
  std::strncpy( playerInfo_.cname, newName.c_str(), newName.length() );
}

int PlayerData::getCarriedItem() const
{
  return clientSidePlayerInfo_.citem;
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

std::string PlayerData::getOkeyName() const
{
  return okey_.name;
}

PlayerData::OkeyPasswordType PlayerData::getPasswordOkeyValues() const
{
  return std::make_tuple( okey_.pass1, okey_.pass2 );
}

void PlayerData::setUserNumber( long unsigned int usnr )
{
  okey_.usnr = usnr;
}

unsigned int PlayerData::getOkeyUserNumber() const
{
  return okey_.usnr;
}

void PlayerData::setXButton( xbutton button, int index )
{
  playerInfo_.xbutton[ index ] = button;
}

const xbutton& PlayerData::getXButton( int index )
{
  return playerInfo_.xbutton[ index ];
}

void PlayerData::clear()
{
  playerInfo_           = pdata();
  clientSidePlayerInfo_ = cplayer();
  okey_                 = key();
  unique1_              = 0;
  unique2_              = 0;
}

// This is only expected to be called with the electron-UI info
void PlayerData::fromJson( Json::Value& json )
{
  const std::string playerName        = json[ "name" ].asString();
  const std::string playerDescription = json[ "desc" ].asString();
  const std::string playerPass        = json[ "pass" ].asString();
  setName( playerName );

  std::strncpy( const_cast< char* >( okey_.name ), playerName.c_str(), playerName.length() );
  std::strncpy( const_cast< char* >( clientSidePlayerInfo_.name ), playerName.c_str(), playerName.length() );
  std::strncpy( const_cast< char* >( playerInfo_.desc ), playerDescription.c_str(), 160 - 1 );
  password_ = playerPass;

  int sexInt  = json[ "sex" ].asInt();
  int raceInt = json[ "race" ].asInt();

  MenAmongGods::Sex  sex = sexInt == 1 ? MenAmongGods::Sex::Male : MenAmongGods::Sex::Female;
  MenAmongGods::Race race {};

  switch ( raceInt )
  {
  case 1:
    race = MenAmongGods::Race::Templar;
    break;
  case 2:
    race = MenAmongGods::Race::Harakim;
    break;
  case 3:
    race = MenAmongGods::Race::Mercenary;
    break;
  default:
    race = MenAmongGods::Race::Mercenary;
    break;
  }

  okey_.race = getOkeyRaceValue( race, sex );
}

void PlayerData::loadFromJsonFile( const std::string& fileName )
{
  std::ifstream playerFile { fileName };

  //
  // Player data
  //
  Json::Value root {};

  playerFile >> root;

  std::strncpy( playerInfo_.cname, root[ "pdata" ][ "name" ].asCString(), 80 - 1 );
  std::strncpy( playerInfo_.desc, root[ "pdata" ][ "desc" ].asCString(), 160 - 1 );
  std::strncpy( playerInfo_.ref, root[ "pdata" ][ "ref" ].asCString(), 80 - 1 );
  playerInfo_.show_names = root[ "pdata" ][ "show_names" ].asInt();
  playerInfo_.show_proz  = root[ "pdata" ][ "show_percent_health" ].asInt();

  // X-buttons
  for ( int i = 0; i < 12; ++i )
  {
    std::strncpy( playerInfo_.xbutton[ i ].name, root[ "pdata" ][ "xbutton" ][ i ][ "name" ].asCString(), 8 - 1 );
    playerInfo_.xbutton[ i ].skill_nr = root[ "pdata" ][ "xbutton" ][ i ][ "skill_id" ].asInt();
  }

  //
  // key data
  //
  okey_.usnr  = root[ "key" ][ "usnr" ].asUInt();
  okey_.pass1 = root[ "key" ][ "pass1" ].asUInt();
  okey_.pass2 = root[ "key" ][ "pass2" ].asUInt();
  std::strncpy( okey_.name, root[ "key" ][ "name" ].asCString(), 40 - 1 );
  okey_.race = root[ "key" ][ "race" ].asInt();

  //
  // unique values
  //
  unique1_ = root[ "unique1" ].asInt();
  unique2_ = root[ "unique2" ].asInt();
}

// save_options and save_unique combined
void PlayerData::saveToJsonFile( const std::string& fileName ) const
{
  std::string fullFilePath = MenAmongGods::getConfigPath() + fileName + ".moa";

  if ( fileName.empty() )
  {
    std::string playerName = getClientSidePlayerInfo().name;

    if ( playerName.empty() )
    {
      fullFilePath = MenAmongGods::getConfigPath() + "playerData.moa";
    }
    else
    {
      fullFilePath = MenAmongGods::getConfigPath() + playerName + ".moa";
    }
  }

  std::ofstream playerFile( fullFilePath );

  //
  // Player data
  //
  Json::Value root {};

  root[ "pdata" ]                          = Json::objectValue;
  root[ "pdata" ][ "name" ]                = playerInfo_.cname;
  root[ "pdata" ][ "desc" ]                = playerInfo_.desc;
  root[ "pdata" ][ "ref" ]                 = playerInfo_.ref;
  root[ "pdata" ][ "changed" ]             = playerInfo_.changed;
  root[ "pdata" ][ "show_names" ]          = playerInfo_.show_names;
  root[ "pdata" ][ "show_percent_health" ] = playerInfo_.show_proz;
  root[ "pdata" ][ "xbutton" ]             = Json::arrayValue;

  for ( unsigned int i = 0; i < 12; ++i )
  {
    Json::Value xbJson {};

    xbJson[ "name" ]     = playerInfo_.xbutton[ i ].name;
    xbJson[ "skill_id" ] = playerInfo_.xbutton[ i ].skill_nr;

    root[ "pdata" ][ "xbutton" ].append( xbJson );
  }

  //
  // key data
  //
  root[ "key" ]            = Json::objectValue;
  root[ "key" ][ "usnr" ]  = okey_.usnr;
  root[ "key" ][ "pass1" ] = okey_.pass1;
  root[ "key" ][ "pass2" ] = okey_.pass2;
  root[ "key" ][ "name" ]  = okey_.name;
  root[ "key" ][ "race" ]  = okey_.race;

  //
  // unique values
  //
  root[ "unique1" ] = unique1_;
  root[ "unique2" ] = unique2_;

  playerFile << root.toStyledString();

  std::cerr << "Saved player file to: ./" << fullFilePath << std::endl;
}
