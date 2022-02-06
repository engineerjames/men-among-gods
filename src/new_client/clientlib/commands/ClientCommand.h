#ifndef MEN_AMONG_GODS_CLIENT_COMMAND_H
#define MEN_AMONG_GODS_CLIENT_COMMAND_H

#include "ClientTypes.h"

#include <SFML/Network.hpp>

namespace MenAmongGods
{
template < typename CmdType, CmdType CmdVal > class ClientCommand
{
public:
  CmdType type                                     = CmdVal;
  virtual ~ClientCommand()                         = default;
  virtual void send( sf::TcpSocket& socket ) const = 0;

protected:
  void sendOneArgument( sf::TcpSocket& socket, std::uint32_t x ) const
  {
    unsigned char buf[ 16 ] {};

    buf[ 0 ] = static_cast< unsigned char >( CmdVal );

    *( std::uint32_t* ) ( buf + 1 ) = x;

    std::size_t bytesSent = 0;

    while ( bytesSent != 16 )
    {
      socket.send( buf, sizeof( buf ), bytesSent );
    }
  }

  void sendTwoArguments( sf::TcpSocket& socket, std::uint16_t x, std::uint32_t y ) const
  {
    unsigned char buf[ 16 ] {};

    buf[ 0 ] = static_cast< unsigned char >( CmdVal );

    *( std::uint16_t* ) ( buf + 1 ) = x;
    *( std::uint32_t* ) ( buf + 3 ) = y;

    std::size_t bytesSent = 0;

    while ( bytesSent != 16 )
    {
      socket.send( buf, sizeof( buf ), bytesSent );
    }
  }

  void sendThreeArguments( sf::TcpSocket& socket, std::uint32_t x, std::uint32_t y, std::uint32_t z ) const
  {
    unsigned char buf[ 16 ] {};

    buf[ 0 ] = static_cast< unsigned char >( CmdVal );

    *( std::uint32_t* ) ( buf + 1 ) = x;
    *( std::uint32_t* ) ( buf + 5 ) = y;
    *( std::uint32_t* ) ( buf + 9 ) = z;

    std::size_t bytesSent = 0;

    while ( bytesSent != 16 )
    {
      socket.send( buf, sizeof( buf ), bytesSent );
    }
  }
};
} // namespace MenAmongGods

#endif