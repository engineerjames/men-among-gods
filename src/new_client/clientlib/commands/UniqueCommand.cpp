#include "UniqueCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>
#include <iostream>

namespace MenAmongGods
{
UniqueCommand::UniqueCommand( std::uint32_t unique1, std::uint32_t unique2 )
    : ClientCommand( ClientMessages::MessageTypes::CMD_UNIQUE )
    , unique1_( unique1 )
    , unique2_( unique2 )
{
}

bool UniqueCommand::send( sf::TcpSocket& socket ) const
{
  std::array< std::uint8_t, 16 > buf {};

  buf[ 0 ]                               = ClientMessages::getValue( ClientMessages::MessageTypes::CMD_UNIQUE );
  *( unsigned long* ) ( buf.data() + 1 ) = unique1_;
  *( unsigned long* ) ( buf.data() + 5 ) = unique2_;
  std::cerr << "Sending CL_CMD_UNIQUE...\n";
  std::cerr << "unique1_ = " << unique1_ << std::endl;
  std::cerr << "unique2_ = " << unique2_ << std::endl;

  // sf::Socket::Status status =
  socket.send( buf.data(), buf.size() );

  return true; // status == sf::Socket::Status::Done;
}
} // namespace MenAmongGods