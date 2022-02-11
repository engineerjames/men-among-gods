#include "StatCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
StatCommand::StatCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand( ClientMessages::MessageTypes::CMD_STAT )
    , x_( x )
    , y_( y )
{
}

bool StatCommand::send( sf::TcpSocket& socket ) const
{
  return StatCommand::sendTwoArguments( socket, x_, y_ );
}

Json::Value StatCommand::toJson() const
{
  Json::Value root = MenAmongGods::ClientCommand::toJson();
  root[ "x" ]      = x_;
  root[ "y" ]      = y_;

  return root;
}

} // namespace MenAmongGods