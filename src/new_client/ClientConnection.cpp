#include "ClientConnection.h"

#include <cstring>
#include <iostream>

#include "ClientMessage.h"
#include "Encoder.h"
#include "PlayerData.h"
#include "ServerMessage.h"
#include "TickBuffer.h"

ClientConnection::ClientConnection( std::string hostIp, unsigned short hostPort )
    : clientSocket_()
    , hostIpAddress_( hostIp )
    , hostPort_( hostPort )
    , isConnected_( false )
    , unique1_( 0 )
    , unique2_( 0 )
    , serverVersion_( 0 )
    , clientData_()
    , tickCount_( 0 )
{
}

bool ClientConnection::connect()
{
  sf::Socket::Status status = clientSocket_.connect( hostIpAddress_, hostPort_ );
  isConnected_              = status == sf::Socket::Status::Done;
  return isConnected_;
}

bool ClientConnection::login()
{
  if ( ! isConnected_ )
  {
    // TODO: Need better error handling
    std::cerr << "Attempting to login while not connected!" << std::endl;
    return false;
  }

  std::array< std::uint8_t, 16 > buffer {};

  // Send password infomation
  // Hard-code an empty password for now, but no need to send it
  // since the legacy code just sent a 0-initialized byte buffer if
  // the password was empty... I think.
  std::cerr << "Sending initial password...\n";
  const std::string myEmptyPassword = "";
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

    procStatus = processLoginResponse( buffer );
    if ( procStatus == ProcessStatus::ERROR )
    {
      std::cerr << "Error logging in!" << std::endl;
      return false;
    }
  } while ( procStatus == ProcessStatus::CONTINUE );

  return true;
}

// Returns 0 1, -1; TODO: Add checks for if connected...
ClientConnection::ProcessStatus ClientConnection::processLoginResponse( const std::array< std::uint8_t, 16 >& buffer )
{
  unsigned int                   tmp {};
  std::array< std::uint8_t, 16 > outputBuffer {};
  std::array< char, 256 >        messageOfTheDay {};
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
    *( unsigned long* ) ( outputBuffer.data() + 9 ) = 1;
    std::cerr << "Sending CL_CHALLENGE...\n";
    clientSocket_.send( outputBuffer.data(), outputBuffer.size() );

    outputBuffer[ 0 ]                               = ClientMessages::getValue( ClientMessages::MessageTypes::CMD_UNIQUE );
    *( unsigned long* ) ( outputBuffer.data() + 1 ) = unique1_;
    *( unsigned long* ) ( outputBuffer.data() + 5 ) = unique2_;
    std::cerr << "Sending CL_CMD_UNIQUE...\n";
    clientSocket_.send( outputBuffer.data(), outputBuffer.size() );

    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::NEWPLAYER )
  {
    clientData_.usnr  = *( unsigned long* ) ( buffer.data() + 1 ); // Unique player ID
    clientData_.pass1 = *( unsigned long* ) ( buffer.data() + 5 );
    clientData_.pass2 = *( unsigned long* ) ( buffer.data() + 9 );
    serverVersion_    = *( unsigned char* ) ( buffer.data() + 13 );
    serverVersion_ += ( int ) ( ( *( unsigned char* ) ( buffer.data() + 14 ) ) ) << 8;
    serverVersion_ += ( int ) ( ( *( unsigned char* ) ( buffer.data() + 15 ) ) ) << 16;
    std::cerr << "Server Response: NEWPLAYER...\n";
    std::cerr << "received usnr:" << clientData_.usnr << std::endl;
    std::cerr << "received pass1:" << clientData_.pass1 << std::endl;
    std::cerr << "received pass2:" << clientData_.pass2 << std::endl;
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
    // TODO: Add reason from tmp
    std::cerr << "STATUS: Server demands exit.\n";

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
    std::memcpy( messageOfTheDay.data(), buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD1...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD2 )
  {
    std::memcpy( messageOfTheDay.data() + 15, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD2...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD3 )
  {
    std::memcpy( messageOfTheDay.data() + 30, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD3...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD4 )
  {
    std::memcpy( messageOfTheDay.data() + 45, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD4...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD5 )
  {
    std::memcpy( messageOfTheDay.data() + 60, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD5...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD6 )
  {
    std::memcpy( messageOfTheDay.data() + 75, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD6...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD7 )
  {
    std::memcpy( messageOfTheDay.data() + 90, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD7...\n";
    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::MOD8 )
  {
    std::memcpy( messageOfTheDay.data() + 105, buffer.data() + 1, 15 );
    std::cerr << "Server Response: MOD8...\n";
    return ProcessStatus::CONTINUE;
  }
  else
  {
    return ProcessStatus::CONTINUE;
  }
}

void ClientConnection::moveOnce()
{
  unsigned char buf[ 16 ] {};

  buf[ 0 ]                         = ClientMessages::getValue( ClientMessages::MessageTypes::CMD_MOVE );
  *( unsigned short* ) ( buf + 1 ) = ( short ) 514;
  *( unsigned long* ) ( buf + 3 )  = ( long ) 514;

  std::size_t bytesSent = 0;

  while ( bytesSent != 16 )
  {
    clientSocket_.send( buf, sizeof( buf ), bytesSent );
  }

  std::cerr << "Done sending move command!" << std::endl;
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
  std::array< uint8_t, 16 > buf {};
  buf[ 0 ]                              = ClientMessages::getValue( ClientMessages::MessageTypes::CMD_CTICK );
  *( unsigned int* ) ( buf.data() + 1 ) = tickCount_;

  // Increment tickCount
  tickCount_ += 16;

  std::size_t        dataSent {};
  sf::Socket::Status status = clientSocket_.send( buf.data(), buf.size(), dataSent );

  return status == sf::Socket::Status::Done;
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