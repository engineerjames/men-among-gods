#include "ClientConnection.h"

#include <cstring>
#include <iostream>

#include "ClientMessage.h"
#include "Encoder.h"
#include "ServerMessage.h"

ClientConnection::ClientConnection( std::string hostIp, unsigned short hostPort )
    : clientSocket_()
    , hostIpAddress_( hostIp )
    , hostPort_( hostPort )
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
  int tmp = 0;
  do
  {
    std::size_t        bytesReceived = 0;
    sf::Socket::Status status        = clientSocket_.receive( buffer.data(), sizeof( buffer ), bytesReceived );
    if ( bytesReceived == 0 || status == sf::Socket::Status::Disconnected )
    {
      std::cerr << "STATUS: ERROR: Server closed connection.\n";
      return false;
    }

    tmp = processLoginResponse( buffer );
    if ( tmp == -1 )
    {
      std::cerr << "Error logging in!" << std::endl;
      return false;
    }
  } while ( tmp == 0 );

  return true;
}

bool ClientConnection::processLoginResponse( const std::array< std::uint8_t, 16 > &buffer )
{
  unsigned int                   tmp {};
  std::array< std::uint8_t, 16 > outputBuffer {};
  std::array< char, 256 >        messageOfTheDay {};
  static int                     capcnt {};
  static char                    mod[ 256 ] {};

  ServerMessages::MessageTypes serverMsgType = ServerMessages::getType( buffer[ 0 ] );

  using ServerMessages::MessageTypes;

  if ( serverMsgType == MessageTypes::CHALLENGE )
  {
    tmp = *( unsigned long * ) ( buffer.data() + 1 );
    tmp = Encoder::xcrypt( tmp );

    outputBuffer[ 0 ]                                = ClientMessages::getValue( ClientMessages::MessageTypes::CHALLENGE );
    *( unsigned long * ) ( outputBuffer.data() + 1 ) = tmp;
    *( unsigned long * ) ( outputBuffer.data() + 5 ) = VERSION;
    *( unsigned long * ) ( outputBuffer.data() + 9 ) = 1;
    std::cerr << "Sending CL_CHALLENGE...\n";
    clientSocket_.send( outputBuffer.data(), outputBuffer.size() );

    outputBuffer[ 0 ]                 = ClientMessages::getValue( ClientMessages::MessageTypes::CMD_UNIQUE );
    *( unsigned long * ) ( outputBuffer.data() + 1 ) = unique1_;
    *( unsigned long * ) ( outputBuffer.data() + 5 ) = unique2_;
    std::cerr << "Sending CL_CMD_UNIQUE...\n";
    clientSocket_.send( outputBuffer.data(), outputBuffer.size() );

    capcnt = 0;

    return 0;
  }
  else if ( serverMsgType == MessageTypes::NEWPLAYER )
  {
  }
  else if ( serverMsgType == MessageTypes::LOGIN_OK )
  {
  }
  else if ( serverMsgType == MessageTypes::EXIT )
  {
  }
  else if ( serverMsgType == MessageTypes::CAP )
  {
  }
  else if ( serverMsgType == MessageTypes::MOD1 )
  {
  }
  else if ( serverMsgType == MessageTypes::MOD2 )
  {
  }
  else if ( serverMsgType == MessageTypes::MOD3 )
  {
  }
  else if ( serverMsgType == MessageTypes::MOD4 )
  {
  }
  else if ( serverMsgType == MessageTypes::MOD5 )
  {
  }
  else if ( serverMsgType == MessageTypes::MOD6 )
  {
  }
  else if ( serverMsgType == MessageTypes::MOD7 )
  {
  }
  else if ( serverMsgType == MessageTypes::MOD8 )
  {
  }
  else
  {
    return false;
  }

  if ( buffer[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::CHALLENGE ) )
  { // answer challenges at once
    // SetDlgItemText(hwnd, IDC_STATUS, "STATUS: Login Part I");
  }
  if ( buffer[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::NEWPLAYER ) )
  {                                                // answer newplayer at once
    okey.usnr  = *( unsigned long * ) ( buf + 1 ); // Unique player ID
    okey.pass1 = *( unsigned long * ) ( buf + 5 );
    okey.pass2 = *( unsigned long * ) ( buf + 9 );
    ser_ver    = *( unsigned char * ) ( buf + 13 );
    ser_ver += ( int ) ( ( *( unsigned char * ) ( buf + 14 ) ) ) << 8;
    ser_ver += ( int ) ( ( *( unsigned char * ) ( buf + 15 ) ) ) << 16;
    std::cerr << "Server Response: NEWPLAYER...\n";
    std::cerr << "received usnr:" << okey.usnr << std::endl;
    std::cerr << "received pass1:" << okey.pass1 << std::endl;
    std::cerr << "received pass2:" << okey.pass2 << std::endl;
    return 1;
  }
  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::LOGIN_OK ) )
  {
    ser_ver = *( unsigned long * ) ( buf + 1 );
    std::cerr << "Server Response: LOGIN OK...\n";
    return 1;
  }

  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::EXIT ) )
  {
    tmp = *( unsigned int * ) ( buf + 1 );
    if ( tmp < 1 || tmp > 14 )
    {
      // std::cerr << "STATUS: Server demands exit:\nunknown reason";
    }
    std::cerr << "STATUS: Server demands exit.\n";

    return -1;
  }

  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::CAP ) )
  {
    tmp = *( unsigned int * ) ( buf + 1 );
    capcnt++;
    std::cerr << "STATUS: Player limit reached. You're in queue.\n";
    return 0;
  }

  // Message of the Day Processing
  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::MOD1 ) )
  {
    std::memcpy( mod, buf + 1, 15 );
    std::cerr << "Server Response: MOD1...\n";
    return 0;
  }
  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::MOD2 ) )
  {
    std::memcpy( mod + 15, buf + 1, 15 );
    std::cerr << "Server Response: MOD2...\n";
    return 0;
  }
  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::MOD3 ) )
  {
    std::memcpy( mod + 30, buf + 1, 15 );
    std::cerr << "Server Response: MOD3...\n";
    return 0;
  }
  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::MOD4 ) )
  {
    std::memcpy( mod + 45, buf + 1, 15 );
    std::cerr << "Server Response: MOD4...\n";
    return 0;
  }
  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::MOD5 ) )
  {
    std::memcpy( mod + 60, buf + 1, 15 );
    std::cerr << "Server Response: MOD5...\n";
    return 0;
  }
  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::MOD6 ) )
  {
    std::memcpy( mod + 75, buf + 1, 15 );
    std::cerr << "Server Response: MOD6...\n";
    return 0;
  }
  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::MOD7 ) )
  {
    std::memcpy( mod + 90, buf + 1, 15 );
    std::cerr << "Server Response: MOD7...\n";
    return 0;
  }
  if ( buf[ 0 ] == ServerMessages::getValue( ServerMessages::MessageTypes::MOD8 ) )
  {
    std::memcpy( mod + 105, buf + 1, 15 );
    std::cerr << "Server Response: MOD8...\n";
    std::cerr << mod << std::endl;
    return 0;
  }

  return 0;
  return false;
}

ClientConnection::~ClientConnection()
{
  clientSocket_.disconnect();
}