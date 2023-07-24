#include "PlayerData.h"

#include <cstring>
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

#include "ClientConfiguration.h"
#include "ClientTypes.h"
#include "ColorPalette.h"
#include "Constants.h"
#include "InventoryConstants.h"
#include "Logger.h"
#include "RaceAndSex.h"
#include "RankNames.h"
#include "ResourceLocations.h"
#include "UtilityFunctions.h"

// NOLINTNEXTLINE
std::map< unsigned short, looks > PlayerData::lookMap_ {};

// NOLINTNEXTLINE
int PlayerData::lookAt_ {};

PlayerData::PlayerData( const sf::RenderWindow& window, const MenAmongGods::FontCache& fontCache )
    : window_( window )
    , fontCache_( fontCache )
    , playerInfo_()
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
    , playerIsHoldingShift_( false )
    , playerIsHoldingControl_( false )
    , exitFlag_( false )
    , hoverState_( PlayerData::HoverState::NONE )
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

void PlayerData::update()
{
  playerIsHoldingShift_   = sf::Keyboard::isKeyPressed( sf::Keyboard::LShift );
  playerIsHoldingControl_ = sf::Keyboard::isKeyPressed( sf::Keyboard::LControl );
}

void PlayerData::setExitFlag( bool newValue )
{
  exitFlag_ = newValue;
}

bool PlayerData::getExitFlag() const
{
  return exitFlag_;
}

void PlayerData::setHoverState( PlayerData::HoverState state )
{
  hoverState_ = state;
}

PlayerData::HoverState PlayerData::getHoverState() const
{
  return hoverState_;
}

void PlayerData::onUserInput( const sf::Event& )
{
}

void PlayerData::finalize()
{
}

void PlayerData::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  std::string mouseText = "";

  switch ( hoverState_ )
  {
  case PlayerData::HoverState::PICKUP:
    mouseText = "Pickup";
    break;
  case PlayerData::HoverState::ATTACK:
    mouseText = "Attack";
    break;
  case PlayerData::HoverState::GIVE:
    mouseText = "Give";
    break;
  case PlayerData::HoverState::USE:
    mouseText = "Use";
    break;
  case PlayerData::HoverState::DROP:
    mouseText = "Drop";
    break;
  case PlayerData::HoverState::NONE:
  default:
    // Do nothing
    break;
  }

  sf::Text mouseTextToDraw { mouseText, fontCache_.getFont(), 9 };
  mouseTextToDraw.setOutlineColor( sf::Color::Black );
  mouseTextToDraw.setOutlineThickness( 1 );
  mouseTextToDraw.setFillColor( MenAmongGods::MsgYellow );

  auto mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );

  mousePosition += sf::Vector2f { 5.0f, 9.0f };

  mouseTextToDraw.setPosition( mousePosition );

  target.draw( mouseTextToDraw, states );
}

bool PlayerData::isHoldingShift() const
{
  return playerIsHoldingShift_;
}

bool PlayerData::isHoldingControl() const
{
  return playerIsHoldingControl_;
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
  int         rank       = getRank();
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
  return MenAmongGods::points2rank( clientSidePlayerInfo_.points_tot );
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
  // TODO: Before this PR merges, this '30' value needs to be synchronized with the frame rate.
  lookTimer_ += ( 1.0f / CLIENT_FRAME_LIMIT );

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
void PlayerData::fromJson( nlohmann::json& json )
{
  const std::string playerName        = json[ "name" ].get<std::string>();
  const std::string playerDescription = json[ "desc" ].get<std::string>();
  const std::string playerPass        = json[ "pass" ].get<std::string>();
  setName( playerName );

  LOG_DEBUG("Logging in with parameter: " << json.dump());

  std::strncpy( const_cast< char* >( okey_.name ), playerName.c_str(), playerName.length() );
  std::strncpy( const_cast< char* >( clientSidePlayerInfo_.name ), playerName.c_str(), playerName.length() );
  std::strncpy( const_cast< char* >( playerInfo_.desc ), playerDescription.c_str(), 160 - 1 );
  password_ = playerPass;

  int sexInt  = json[ "sex" ].get<int>();
  int raceInt = json[ "race" ].get<int>();

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
  nlohmann::json root {};

  playerFile >> root;

  std::strncpy( playerInfo_.cname, root[ "pdata" ][ "name" ].get<std::string>().c_str(), 80 - 1 );
  std::strncpy( playerInfo_.desc, root[ "pdata" ][ "desc" ].get<std::string>().c_str(), 160 - 1 );
  std::strncpy( playerInfo_.ref, root[ "pdata" ][ "ref" ].get<std::string>().c_str(), 80 - 1 );
  playerInfo_.show_names = root[ "pdata" ][ "show_names" ].get<int>();
  playerInfo_.show_proz  = root[ "pdata" ][ "show_percent_health" ].get<int>();

  // X-buttons
  for ( int i = 0; i < 12; ++i )
  {
    std::strncpy( playerInfo_.xbutton[ i ].name, root[ "pdata" ][ "xbutton" ][ i ][ "name" ].get<std::string>().c_str(), 8 - 1 );
    playerInfo_.xbutton[ i ].skill_nr = root[ "pdata" ][ "xbutton" ][ i ][ "skill_id" ].get<int>();
  }

  //
  // key data
  //
  okey_.usnr  = root[ "key" ][ "usnr" ].get<unsigned int>();
  okey_.pass1 = root[ "key" ][ "pass1" ].get<unsigned int>();
  okey_.pass2 = root[ "key" ][ "pass2" ].get<unsigned int>();
  std::strncpy( okey_.name, root[ "key" ][ "name" ].get<std::string>().c_str(), 40 - 1 );
  okey_.race = root[ "key" ][ "race" ].get<int>();

  //
  // unique values
  //
  unique1_ = root[ "unique1" ].get<int>();
  unique2_ = root[ "unique2" ].get<int>();
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
  nlohmann::json root {};

  // TODO: Confirm if this is needed?
  //root[ "pdata" ]                          = json::object();
  root[ "pdata" ][ "name" ]                = playerInfo_.cname;
  root[ "pdata" ][ "desc" ]                = playerInfo_.desc;
  root[ "pdata" ][ "ref" ]                 = playerInfo_.ref;
  root[ "pdata" ][ "changed" ]             = playerInfo_.changed;
  root[ "pdata" ][ "show_names" ]          = playerInfo_.show_names;
  root[ "pdata" ][ "show_percent_health" ] = playerInfo_.show_proz;
  //root[ "pdata" ][ "xbutton" ]             = json::array();

  std::array<nlohmann::json, 12> xButtonArray{};
  for ( unsigned int i = 0; i < 12; ++i )
  {
    nlohmann::json xbJson {};

    xbJson[ "name" ]     = playerInfo_.xbutton[ i ].name;
    xbJson[ "skill_id" ] = playerInfo_.xbutton[ i ].skill_nr;

    xButtonArray[i] = xbJson;
  }

  root["pdata"]["xbutton"] = xButtonArray;

  //
  // key data
  //
  // root[ "key" ]            = Json::objectValue;
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

  playerFile << root.dump();

  std::cerr << "Saved player file to: ./" << fullFilePath << std::endl;
}
