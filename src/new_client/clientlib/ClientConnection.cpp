#include "ClientConnection.h"

#include <array>
#include <cstring>

#include "ClientMessage.h"
#include "ConversionUtilities.h"
#include "Encoder.h"
#include "Logger.h"
#include "PlayerData.h"
#include "ServerMessage.h"
#include "TickBuffer.h"

// Commands
#include "AutoLookCommand.h"
#include "ChallengeCommand.h"
#include "LoginCommand.h"
#include "NewLoginCommand.h"
#include "PasswordCommand.h"
#include "SayCommand.h"
#include "SetUserCommand.h"
#include "TickCommand.h"
#include "UniqueCommand.h"

namespace
{
static const std::array< const char*, 15 > logout_reason = {
    "unknown",                                                                              // 0
    "Client failed challenge.",                                                             // 1
    "Client was idle too long.",                                                            // 2
    "No room to drop character.",                                                           // 3
    "Invalid parameters.",                                                                  // 4
    "Character already active or no player character.",                                     // 5
    "Invalid password.",                                                                    // 6
    "Client too slow.",                                                                     // 7
    "Receive failure.",                                                                     // 8
    "Server is being shutdown.",                                                            // 9
    "You entered a Tavern.",                                                                // 10
    "Client version too old. Update needed.",                                               // 11
    "Aborting on user request.",                                                            // 12
    "this should never show up",                                                            // 13
    "You have been banned for an hour. Enhance your social behaviour before you come back." // 14
};
}

ClientConnection::ClientConnection( std::string hostIp, unsigned short hostPort )
    : clientSocket_()
    , hostIpAddress_( hostIp )
    , hostPort_( hostPort )
    , isConnected_( false )
    , unique1_( 0 )
    , unique2_( 0 )
    , serverVersion_( 0 )
    , tickCount_( 0 )
    , messageOfTheDay_()
{
}

bool ClientConnection::connect()
{
  LOG_DEBUG( "Logging in with hostIpAddress=" << hostIpAddress_ << " and hostPort=" << hostPort_ );
  sf::Socket::Status status = clientSocket_.connect( hostIpAddress_, hostPort_ );
  isConnected_              = status == sf::Socket::Status::Done;
  return isConnected_;
}

void ClientConnection::getUnknownPlayerIds( const PlayerData& playerData )
{
  auto ids = playerData.getUnknownCharacterIds();
  for ( const auto& id : ids )
  {
    auto command = std::make_unique< MenAmongGods::AutoLookCommand >( id );
    command->send( clientSocket_ );
  }
}

bool ClientConnection::login( PlayerData& playerData )
{
  if ( ! isConnected_ )
  {
    LOG_ERROR( "Attempting to login while not connected!" );
    return false;
  }

  std::array< std::uint8_t, 16 > buffer {};

  LOG_DEBUG( "Sending initial password..." );
  MenAmongGods::PasswordCommand passwordCommand { playerData.getPassword() };
  passwordCommand.send( clientSocket_ );

  // Player is already known to the server?
  if ( playerData.getOkeyUserNumber() != 0 )
  {
    LOG_DEBUG( "Sending known player login request..." );
    auto [ pass1, pass2 ] = playerData.getPasswordOkeyValues();
    MenAmongGods::LoginCommand loginCommand { playerData.getOkeyUserNumber(), pass1, pass2 };
    loginCommand.send( clientSocket_ ); // usnr // pass1 //pass2
  }
  else
  {
    LOG_DEBUG( "Sending new player login request..." );
    MenAmongGods::NewLoginCommand newLoginCommand {};
    newLoginCommand.send( clientSocket_ );
  }

  LOG_DEBUG( "Waiting for receipt of information..." );
  ProcessStatus procStatus = ProcessStatus::CONTINUE;
  do
  {
    std::size_t        bytesReceived = 0;
    sf::Socket::Status status        = clientSocket_.receive( buffer.data(), buffer.size(), bytesReceived );
    if ( bytesReceived == 0 || status == sf::Socket::Status::Disconnected )
    {
      LOG_ERROR( "STATUS: ERROR: Server closed connection." );
      return false;
    }

    procStatus = processLoginResponse( playerData, buffer );
    if ( procStatus == ProcessStatus::ERROR )
    {
      LOG_ERROR( "Error logging in!" );
      return false;
    }
  } while ( procStatus == ProcessStatus::CONTINUE );

  return true;
}

ClientConnection::ProcessStatus ClientConnection::processLoginResponse( PlayerData&                           playerData,
                                                                        const std::array< std::uint8_t, 16 >& buffer )
{
  if ( ! isConnected_ )
  {
    LOG_ERROR( "Can't execute processLoginResponse - Socket is not connected!" );
    return ClientConnection::ProcessStatus::ERROR;
  }

  std::uint32_t tmp {};
  static int    capcnt {};

  ServerMessages::MessageTypes serverMsgType = ServerMessages::getType( buffer[ 0 ] );

  using ServerMessages::MessageTypes;

  if ( serverMsgType == MessageTypes::CHALLENGE )
  {
    std::memcpy( &tmp, buffer.data() + 1, sizeof( tmp ) );
    tmp = Encoder::xcrypt( tmp );

    MenAmongGods::ChallengeCommand challengeCommand { tmp, VERSION, playerData.getRaceAndSex() };
    challengeCommand.send( clientSocket_ );

    MenAmongGods::UniqueCommand uniqueCommand { unique1_, unique2_ };
    uniqueCommand.send( clientSocket_ );

    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::NEWPLAYER )
  {
    // Unique player ID
    std::uint32_t clientDataUserNumber {};
    std::uint32_t clientDataPass1 {};
    std::uint32_t clientDataPass2 {};

    std::memcpy( &clientDataUserNumber, buffer.data() + 1, sizeof( std::uint32_t ) );
    std::memcpy( &clientDataPass1, buffer.data() + 5, sizeof( std::uint32_t ) );
    std::memcpy( &clientDataPass2, buffer.data() + 9, sizeof( std::uint32_t ) );

    playerData.setUserNumber( clientDataUserNumber );
    playerData.setPassword( clientDataPass1, clientDataPass2 );

    serverVersion_ = *( unsigned char* ) ( buffer.data() + 13 );
    serverVersion_ += ( int ) ( ( *( unsigned char* ) ( buffer.data() + 14 ) ) ) << 8;
    serverVersion_ += ( int ) ( ( *( unsigned char* ) ( buffer.data() + 15 ) ) ) << 16;

    auto [ storedPass1, storedPass2 ] = playerData.getPasswordOkeyValues();

    LOG_DEBUG( "Received NEWPLAYER message from server: [usnr, pass1, pass2]=[" << playerData.getUserNumber() << ", " << storedPass1 << ", "
                                                                                << storedPass2 << "]." );

    playerData.saveToJsonFile( playerData.getPlayerName() );

    return ProcessStatus::DONE;
  }
  else if ( serverMsgType == MessageTypes::LOGIN_OK )
  {
    std::memcpy( &serverVersion_, buffer.data() + 1, sizeof( std::uint32_t ) );
    LOG_DEBUG( "LOGIN_OK from server: " << serverVersion_ );
    return ProcessStatus::DONE;
  }
  else if ( serverMsgType == MessageTypes::EXIT )
  {
    std::memcpy( &tmp, buffer.data() + 1, sizeof( tmp ) );

    LOG_WARNING( "Server demands exit: " << logout_reason[ tmp ] );

    return ProcessStatus::ERROR;
  }
  else if ( serverMsgType == MessageTypes::CAP )
  {
    std::memcpy( &tmp, buffer.data() + 1, sizeof( tmp ) );
    capcnt++;
    LOG_WARNING( "Player limit reached; player placed in queue: " << capcnt << ", " << tmp );
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD1 )
  {
    std::memcpy( messageOfTheDay_.data(), buffer.data() + 1, 15 );
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD2 )
  {
    std::memcpy( messageOfTheDay_.data() + 15, buffer.data() + 1, 15 );
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD3 )
  {
    std::memcpy( messageOfTheDay_.data() + 30, buffer.data() + 1, 15 );
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD4 )
  {
    std::memcpy( messageOfTheDay_.data() + 45, buffer.data() + 1, 15 );
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD5 )
  {
    std::memcpy( messageOfTheDay_.data() + 60, buffer.data() + 1, 15 );
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD6 )
  {
    std::memcpy( messageOfTheDay_.data() + 75, buffer.data() + 1, 15 );
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD7 )
  {
    std::memcpy( messageOfTheDay_.data() + 90, buffer.data() + 1, 15 );
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD8 )
  {
    std::memcpy( messageOfTheDay_.data() + 105, buffer.data() + 1, 15 );
    return ProcessStatus::CONTINUE;
  }
  else
  {
    return ProcessStatus::CONTINUE;
  }
}

std::string ClientConnection::getMessageOfTheDay() const
{
  return MenAmongGods::convertArrayToStdString( messageOfTheDay_ );
}

void ClientConnection::processCommand( std::shared_ptr< MenAmongGods::ClientCommand > command )
{
  command->send( clientSocket_ );
}

bool ClientConnection::sendPlayerData( const PlayerData& playerData )
{
  MenAmongGods::SetUserCommand setUserCommand { playerData.getPlayerName(), playerData.getPlayerDescription() };

  return setUserCommand.send( clientSocket_ );
}

// TODO: Get actual values here (if needed--or remove)
void ClientConnection::sendHardwareInfo()
{
  LOG_DEBUG( "Sending hardware information" );

  std::array< char, 256 > buf {};

  unsigned int langid    = 120;
  unsigned int lcid      = 120;
  std::string  systemDir = "/home/yeah";
  std::string  winDir    = "/home/windir";
  std::string  cDir      = "/home/cdir";
  std::string  user      = "theUser";
  std::string  computer  = "mainComputer";

  std::sprintf( buf.data(), "|langid=%u, lcid=%u", langid, lcid );
  say( buf.data() );
  std::sprintf( buf.data(), "|systemdir=\"%s\"", systemDir.c_str() );
  say( buf.data() );
  std::sprintf( buf.data(), "|windowsdir=\"%s\"", winDir.c_str() );
  say( buf.data() );
  std::sprintf( buf.data(), "|currentdir=\"%s\"", cDir.c_str() );
  say( buf.data() );
  std::sprintf( buf.data(), "|username=\"%s\"", user.c_str() );
  say( buf.data() );
  std::sprintf( buf.data(), "|computername=\"%s\"", computer.c_str() );
  say( buf.data() );
}

void ClientConnection::say( const char* input )
{
  MenAmongGods::SayCommand sayCommand { input };
  sayCommand.send( clientSocket_ );
}

bool ClientConnection::sendTick()
{
  MenAmongGods::TickCommand tickCommand { tickCount_ };

  // Increment tickCount
  tickCount_ += 16;

  bool success = tickCommand.send( clientSocket_ );

  return success;
}

bool ClientConnection::receiveTick( TickBuffer& tickBuffer )
{
  std::size_t received {};

  static std::array< std::uint8_t, 1024 > buffer {};

  clientSocket_.receive( buffer.data(), buffer.size(), received );

  bool successfulTickProcessing = tickBuffer.receive( &buffer, received );

  return successfulTickProcessing;
}

ClientConnection::~ClientConnection()
{
  clientSocket_.disconnect();
}

void ClientConnection::setSocketMode( SocketIOMode newMode )
{
  bool isBlocking = newMode == SocketIOMode::Blocking;

  clientSocket_.setBlocking( isBlocking );
}