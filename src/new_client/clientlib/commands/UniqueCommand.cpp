#include "UniqueCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
UniqueCommand::UniqueCommand( std::int32_t unique1, std::int32_t unique2 )
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

  sf::Socket::Status status = socket.send( buf.data(), buf.size() );

  return status == sf::Socket::Status::Done;
}

Json::Value UniqueCommand::toJson() const
{
  Json::Value root  = MenAmongGods::ClientCommand::toJson();
  root[ "unique1" ] = unique1_;
  root[ "unique2" ] = unique2_;

  return root;
}

} // namespace MenAmongGods