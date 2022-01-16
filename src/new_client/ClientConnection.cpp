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


// Returns 0 1, -1
ClientConnection::ProcessStatus ClientConnection::processLoginResponse( const std::array< std::uint8_t, 16 > &buffer )
{
  unsigned int                   tmp {};
  std::array< std::uint8_t, 16 > outputBuffer {};
  std::array< char, 256 >        messageOfTheDay {};
  static int                     capcnt {};

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

    outputBuffer[ 0 ]                                = ClientMessages::getValue( ClientMessages::MessageTypes::CMD_UNIQUE );
    *( unsigned long * ) ( outputBuffer.data() + 1 ) = unique1_;
    *( unsigned long * ) ( outputBuffer.data() + 5 ) = unique2_;
    std::cerr << "Sending CL_CMD_UNIQUE...\n";
    clientSocket_.send( outputBuffer.data(), outputBuffer.size() );

    return ProcessStatus::CONTINUE;
  }
  else if ( serverMsgType == MessageTypes::NEWPLAYER )
  {
    clientData_.usnr  = *( unsigned long * ) ( buffer.data() + 1 ); // Unique player ID
    clientData_.pass1 = *( unsigned long * ) ( buffer.data() + 5 );
    clientData_.pass2 = *( unsigned long * ) ( buffer.data() + 9 );
    serverVersion_    = *( unsigned char * ) ( buffer.data() + 13 );
    serverVersion_ += ( int ) ( ( *( unsigned char * ) ( buffer.data() + 14 ) ) ) << 8;
    serverVersion_ += ( int ) ( ( *( unsigned char * ) ( buffer.data() + 15 ) ) ) << 16;
    std::cerr << "Server Response: NEWPLAYER...\n";
    std::cerr << "received usnr:" << clientData_.usnr << std::endl;
    std::cerr << "received pass1:" << clientData_.pass1 << std::endl;
    std::cerr << "received pass2:" << clientData_.pass2 << std::endl;
    return ProcessStatus::DONE;
  }
  else if ( serverMsgType == MessageTypes::LOGIN_OK )
  {
    serverVersion_ = *( unsigned long * ) ( buffer.data() + 1 );
    std::cerr << "Server Response: LOGIN OK...\n";
    return ProcessStatus::DONE;
  }
  else if ( serverMsgType == MessageTypes::EXIT )
  {
    tmp = *( unsigned int * ) ( buffer.data() + 1 );
    // TODO: Add reason from tmp
    std::cerr << "STATUS: Server demands exit.\n";

    return ProcessStatus::ERROR;
  }
  else if ( serverMsgType == MessageTypes::CAP )
  {
    tmp = *( unsigned int * ) ( buffer.data() + 1 );
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

ClientConnection::~ClientConnection()
{
  clientSocket_.disconnect();
}