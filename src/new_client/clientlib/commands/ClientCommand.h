#ifndef MEN_AMONG_GODS_CLIENT_COMMAND_H
#define MEN_AMONG_GODS_CLIENT_COMMAND_H

#include "ClientTypes.h"

#include <SFML/Network.hpp>
#include <array>

namespace MenAmongGods
{
template < typename CmdType, CmdType CmdVal > class ClientCommand
{
public:
  CmdType type                                     = CmdVal;
  virtual ~ClientCommand()                         = default;
  virtual bool send( sf::TcpSocket& socket ) const = 0;

protected:
  bool sendOneArgument( sf::TcpSocket& socket, std::uint32_t x ) const
  {
    std::array< uint8_t, 16 > buf {};

    buf[ 0 ] = static_cast< unsigned char >( CmdVal );

    *( std::uint32_t* ) ( buf.data() + 1 ) = x;

    std::size_t bytesSent = 0;

    sf::Socket::Status status = sf::Socket::Status::Done;
    while ( bytesSent != 16 )
    {
      status = socket.send( buf.data(), sizeof( buf ), bytesSent );
    }

    return status == sf::Socket::Status::Done;
  }

  bool sendTwoArguments( sf::TcpSocket& socket, std::uint16_t x, std::uint32_t y ) const
  {
    std::array< uint8_t, 16 > buf {};

    buf[ 0 ] = static_cast< unsigned char >( CmdVal );

    *( std::uint16_t* ) ( buf.data() + 1 ) = x;
    *( std::uint32_t* ) ( buf.data() + 3 ) = y;

    std::size_t bytesSent = 0;

    sf::Socket::Status status = sf::Socket::Status::Done;
    while ( bytesSent != 16 )
    {
      status = socket.send( buf.data(), sizeof( buf ), bytesSent );
    }

    return status == sf::Socket::Status::Done;
  }

  bool sendThreeArguments( sf::TcpSocket& socket, std::uint32_t x, std::uint32_t y, std::uint32_t z ) const
  {
    std::array< uint8_t, 16 > buf {};

    buf[ 0 ] = static_cast< unsigned char >( CmdVal );

    *( std::uint32_t* ) ( buf.data() + 1 ) = x;
    *( std::uint32_t* ) ( buf.data() + 5 ) = y;
    *( std::uint32_t* ) ( buf.data() + 9 ) = z;

    std::size_t bytesSent = 0;

    sf::Socket::Status status = sf::Socket::Status::Done;
    while ( bytesSent != 16 )
    {
      status = socket.send( buf.data(), sizeof( buf ), bytesSent );
    }

    return status == sf::Socket::Status::Done;
  }
};
} // namespace MenAmongGods

#endif