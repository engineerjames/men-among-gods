#include "ClientConnection.h"

#include <cstring>
#include <iostream>

#include "ClientMessage.h"
#include "ConversionUtilities.h"
#include "Encoder.h"
#include "PlayerData.h"
#include "ServerMessage.h"
#include "TickBuffer.h"
#include "TickCommand.h"

namespace
{
static const char* logout_reason[] = {
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
  sf::Socket::Status status = clientSocket_.connect( hostIpAddress_, hostPort_ );
  isConnected_              = status == sf::Socket::Status::Done;
  return isConnected_;
}

bool ClientConnection::login( PlayerData& playerData )
{
  if ( ! isConnected_ )
  {
    std::cerr << "Attempting to login while not connected!" << std::endl;
    return false;
  }

  std::array< std::uint8_t, 16 > buffer {};

  std::cerr << "Sending initial password...\n";
  const std::string myEmptyPassword = playerData.getPassword();
  buffer[ 0 ]                       = ClientMessages::getValue( ClientMessages::MessageTypes::PASSWD );
  clientSocket_.send( buffer.data(), buffer.size() );

  // Assume we're creating a new character each time.
  // Normally you'd need to send the 'key' structure (username, pass1, pass2,
  // etc.)
  std::cerr << "Sending new login request...\n";
  buffer[ 0 ] = ClientMessages::getValue( ClientMessages::MessageTypes::NEWLOGIN );
  clientSocket_.send( buffer.data(), buffer.size() );

  std::cerr << "Waiting for receipt of information...\n";
  ProcessStatus procStatus = ProcessStatus::CONTINUE;
  do
  {
    std::size_t        bytesReceived = 0;
    sf::Socket::Status status        = clientSocket_.receive( buffer.data(), sizeof( buffer ), bytesReceived );
    if ( bytesReceived == 0 || status == sf::Socket::Status::Disconnected )
    {
      std::cerr << "STATUS: ERROR: Server closed connection.\n";
      return false;
    }

    procStatus = processLoginResponse( playerData, buffer );
    if ( procStatus == ProcessStatus::ERROR )
    {
      std::cerr << "Error logging in!" << std::endl;
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
    std::cerr << "Can't execute processLoginResponse - Socket is not connected!" << std::endl;
    return ClientConnection::ProcessStatus::ERROR;
  }

  unsigned int                   tmp {};
  std::array< std::uint8_t, 16 > outputBuffer {};
  static int                     capcnt {};

  ServerMessages::MessageTypes serverMsgType = ServerMessages::getType( buffer[ 0 ] );

  using ServerMessages::MessageTypes;

  if ( serverMsgType == MessageTypes::CHALLENGE )
  {
    tmp = *( unsigned long* ) ( buffer.data() + 1 );
    tmp = Encoder::xcrypt( tmp );

    outputBuffer[ 0 ]                               = ClientMessages::getValue( ClientMessages::MessageTypes::CHALLENGE );
    *( unsigned long* ) ( outputBuffer.data() + 1 ) = tmp;
    *( unsigned long* ) ( outputBuffer.data() + 5 ) = VERSION;
    *( unsigned long* ) ( outputBuffer.data() + 9 ) = playerData.getRaceAndSex();
    std::cerr << "Sending CL_CHALLENGE...\n";
    std::cerr << "tmp: " << tmp << std::endl;
    std::cerr << "VERSION: " << VERSION << std::endl;
    std::cerr << "OkeyRaceInt: " << playerData.getRaceAndSex();

    clientSocket_.send( outputBuffer.data(), outputBuffer.size() );

    outputBuffer[ 0 ]                               = ClientMessages::getValue( ClientMessages::MessageTypes::CMD_UNIQUE );
    *( unsigned long* ) ( outputBuffer.data() + 1 ) = unique1_;
    *( unsigned long* ) ( outputBuffer.data() + 5 ) = unique2_;
    std::cerr << "Sending CL_CMD_UNIQUE...\n";
    std::cerr << "unique1_ = " << unique1_ << std::endl;
    std::cerr << "unique2_ = " << unique2_ << std::endl;

    clientSocket_.send( outputBuffer.data(), outputBuffer.size() );

    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::NEWPLAYER )
  {
    // Unique player ID
    unsigned long clientDataUserNumber = *( unsigned long* ) ( buffer.data() + 1 );
    unsigned long clientDataPass1      = *( unsigned long* ) ( buffer.data() + 5 );
    unsigned long clientDataPass2      = *( unsigned long* ) ( buffer.data() + 9 );

    playerData.setUserNumber( clientDataUserNumber );
    playerData.setPassword( clientDataPass1, clientDataPass2 );

    serverVersion_ = *( unsigned char* ) ( buffer.data() + 13 );
    serverVersion_ += ( int ) ( ( *( unsigned char* ) ( buffer.data() + 14 ) ) ) << 8;
    serverVersion_ += ( int ) ( ( *( unsigned char* ) ( buffer.data() + 15 ) ) ) << 16;

    std::cerr << "Server Response: NEWPLAYER...\n";
    std::cerr << "received usnr:" << playerData.getUserNumber() << std::endl;
    auto [ storedPass1, storedPass2 ] = playerData.getPasswordOkeyValues();
    std::cerr << "received pass1:" << storedPass1 << std::endl;
    std::cerr << "received pass2:" << storedPass2 << std::endl;

    return ProcessStatus::DONE;
  }
  else if ( serverMsgType == MessageTypes::LOGIN_OK )
  {
    serverVersion_ = *( unsigned long* ) ( buffer.data() + 1 );
    std::cerr << "Server Response: LOGIN OK...\n";
    return ProcessStatus::DONE;
  }
  else if ( serverMsgType == MessageTypes::EXIT )
  {
    tmp = *( unsigned int* ) ( buffer.data() + 1 );

    std::cerr << "STATUS: Server demands exit.\n";
    std::cerr << "REASON: " << logout_reason[ tmp ] << std::endl;

    return ProcessStatus::ERROR;
  }
  else if ( serverMsgType == MessageTypes::CAP )
  {
    tmp = *( unsigned int* ) ( buffer.data() + 1 );
    capcnt++;
    std::cerr << "STATUS: Player limit reached. You're in queue.\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD1 )
  {
    std::memcpy( messageOfTheDay_.data(), buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD1...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD2 )
  {
    std::memcpy( messageOfTheDay_.data() + 15, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD2...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD3 )
  {
    std::memcpy( messageOfTheDay_.data() + 30, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD3...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD4 )
  {
    std::memcpy( messageOfTheDay_.data() + 45, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD4...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD5 )
  {
    std::memcpy( messageOfTheDay_.data() + 60, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD5...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD6 )
  {
    std::memcpy( messageOfTheDay_.data() + 75, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD6...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD7 )
  {
    std::memcpy( messageOfTheDay_.data() + 90, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD7...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD8 )
  {
    std::memcpy( messageOfTheDay_.data() + 105, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD8...\n";
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
  int                            state = 0;
  std::array< std::uint8_t, 16 > buffer {};
  int                            n {};
  bool                           completedTransfer = false;

  if ( ! playerData.hasPlayerDataChanged() )
  {
    return false;
  }

  while ( ! completedTransfer )
  {
    buffer[ 0 ] = ClientMessages::getValue( ClientMessages::MessageTypes::CMD_SETUSER );

    switch ( state )
    {
    case 0:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 0;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerName()[ n ];
      }
      std::cerr << "Transfering user data...";
      break;
    case 1:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 13;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerName()[ n + 13 ];
      }
      break;
    case 2:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 26;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerName()[ n + 26 ];
      }
      break;
    case 3:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 39;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerName()[ n + 39 ];
      }
      break;
    case 4:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 52;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerName()[ n + 52 ];
      }
      break;
    case 5:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 65;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerName()[ n + 65 ];
      }
      break;

    case 6:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 0;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n ];
      }
      break;
    case 7:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 13;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 13 ];
      }
      break;
    case 8:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 26;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 26 ];
      }
      break;
    case 9:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 39;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 39 ];
      }
      break;
    case 10:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 52;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 52 ];
      }
      break;
    case 11:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 65;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 65 ];
      }
      break;

    case 12:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 0;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 78 ];
      }
      break;
    case 13:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 13;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 91 ];
      }
      break;
    case 14:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 26;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 104 ];
      }
      break;
    case 15:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 39;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 117 ];
      }
      break;
    case 16:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 52;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 130 ];
      }
      break;
    case 17:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 65;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerData.getPlayerDescription()[ n + 143 ];
      }
      std::cerr << "Transfer done.\n";
      completedTransfer = true;
      break;
    default:
      std::cerr << "Invalid state!" << std::endl;
      return false;
    }

    clientSocket_.send( buffer.data(), buffer.size() );
    state++;
  }

  return completedTransfer;
}

// TODO: Get actual values here (if needed--or remove)
void ClientConnection::sendHardwareInfo()
{
  char buf[ 256 ] {};

  unsigned int langid    = 120;
  unsigned int lcid      = 120;
  std::string  systemDir = "/home/yeah";
  std::string  winDir    = "/home/windir";
  std::string  cDir      = "/home/cdir";
  std::string  user      = "theUser";
  std::string  computer  = "mainComputer";

  std::sprintf( buf, "|langid=%u, lcid=%u", langid, lcid );
  say( buf );
  std::sprintf( buf, "|systemdir=\"%s\"", systemDir.c_str() );
  say( buf );
  std::sprintf( buf, "|windowsdir=\"%s\"", winDir.c_str() );
  say( buf );
  std::sprintf( buf, "|currentdir=\"%s\"", cDir.c_str() );
  say( buf );
  std::sprintf( buf, "|username=\"%s\"", user.c_str() );
  say( buf );
  std::sprintf( buf, "|computername=\"%s\"", computer.c_str() );
  say( buf );
}

void ClientConnection::say( const char* input )
{
  using ClientMessages::MessageTypes;

  int  n;
  char buf[ 16 ];
  buf[ 0 ] = ClientMessages::getValue( MessageTypes::CMD_INPUT1 );
  for ( n = 0; n < 15; n++ )
  {
    buf[ n + 1 ] = input[ n ];
  }
  clientSocket_.send( buf, sizeof( buf ) );

  buf[ 0 ] = ClientMessages::getValue( MessageTypes::CMD_INPUT2 );
  for ( n = 0; n < 15; n++ )
    buf[ n + 1 ] = input[ n + 15 ];
  clientSocket_.send( buf, sizeof( buf ) );

  buf[ 0 ] = ClientMessages::getValue( MessageTypes::CMD_INPUT3 );
  for ( n = 0; n < 15; n++ )
    buf[ n + 1 ] = input[ n + 30 ];
  clientSocket_.send( buf, sizeof( buf ) );

  buf[ 0 ] = ClientMessages::getValue( MessageTypes::CMD_INPUT4 );
  for ( n = 0; n < 15; n++ )
    buf[ n + 1 ] = input[ n + 45 ];
  clientSocket_.send( buf, sizeof( buf ) );

  buf[ 0 ] = ClientMessages::getValue( MessageTypes::CMD_INPUT5 );
  for ( n = 0; n < 15; n++ )
    buf[ n + 1 ] = input[ n + 60 ];
  clientSocket_.send( buf, sizeof( buf ) );

  buf[ 0 ] = ClientMessages::getValue( MessageTypes::CMD_INPUT6 );
  for ( n = 0; n < 15; n++ )
    buf[ n + 1 ] = input[ n + 75 ];
  clientSocket_.send( buf, sizeof( buf ) );

  buf[ 0 ] = ClientMessages::getValue( MessageTypes::CMD_INPUT7 );
  for ( n = 0; n < 15; n++ )
    buf[ n + 1 ] = input[ n + 90 ];
  clientSocket_.send( buf, sizeof( buf ) );

  buf[ 0 ] = ClientMessages::getValue( MessageTypes::CMD_INPUT8 );
  for ( n = 0; n < 15; n++ )
    buf[ n + 1 ] = input[ n + 105 ];
  clientSocket_.send( buf, sizeof( buf ) );
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