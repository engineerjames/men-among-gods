#ifndef MEN_AMONG_GODS_CLIENT_COMMAND_H
#define MEN_AMONG_GODS_CLIENT_COMMAND_H

#include "ClientMessage.h"
#include "Logger.h"

#include <SFML/Network.hpp>
#include <array>
#include <json/json.h>

namespace MenAmongGods
{
class ClientCommand
{
public:
  virtual ~ClientCommand()                         = default;
  virtual bool send( sf::TcpSocket& socket ) const = 0;

  ClientCommand( ClientMessages::MessageTypes type )
      : type_( type )
  {
  }
  ClientCommand( const ClientCommand& ) = default;
  ClientCommand& operator=( const ClientCommand& ) = default;

  virtual Json::Value toJson() const
  {
    Json::Value root {};
    root[ "type" ] = ClientMessages::getName( type_ );

    return root;
  }

protected:
  ClientMessages::MessageTypes type_;

  bool sendOneArgument( sf::TcpSocket& socket, std::uint32_t x ) const
  {
    std::array< uint8_t, 16 > buf {};

    buf[ 0 ] = ClientMessages::getValue( type_ );

    *( std::uint32_t* ) ( buf.data() + 1 ) = x;

    std::size_t bytesSent = 0;

    sf::Socket::Status status = sf::Socket::Status::Done;
    while ( bytesSent != 16 )
    {
      status = socket.send( buf.data(), sizeof( buf ), bytesSent );
    }

    LOG_DEBUG_OBJ( *this, "Successful send." );
    return status == sf::Socket::Status::Done;
  }

  bool sendTwoArguments( sf::TcpSocket& socket, std::uint16_t x, std::uint32_t y ) const
  {
    std::array< uint8_t, 16 > buf {};

    buf[ 0 ] = ClientMessages::getValue( type_ );

    *( std::uint16_t* ) ( buf.data() + 1 ) = x;
    *( std::uint32_t* ) ( buf.data() + 3 ) = y;

    std::size_t bytesSent = 0;

    sf::Socket::Status status = sf::Socket::Status::Done;
    while ( bytesSent != 16 )
    {
      status = socket.send( buf.data(), sizeof( buf ), bytesSent );
    }

    LOG_DEBUG_OBJ( *this, "Successful send." );
    return status == sf::Socket::Status::Done;
  }

  bool sendThreeArguments( sf::TcpSocket& socket, std::uint32_t x, std::uint32_t y, std::uint32_t z ) const
  {
    std::array< uint8_t, 16 > buf {};

    buf[ 0 ] = ClientMessages::getValue( type_ );

    *( std::uint32_t* ) ( buf.data() + 1 ) = x;
    *( std::uint32_t* ) ( buf.data() + 5 ) = y;
    *( std::uint32_t* ) ( buf.data() + 9 ) = z;

    std::size_t bytesSent = 0;

    sf::Socket::Status status = sf::Socket::Status::Done;
    while ( bytesSent != 16 )
    {
      status = socket.send( buf.data(), sizeof( buf ), bytesSent );
    }

    LOG_DEBUG_OBJ( *this, "Successful send." );
    return status == sf::Socket::Status::Done;
  }
};
} // namespace MenAmongGods

#endif