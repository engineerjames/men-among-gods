#include "DropCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
DropCommand::DropCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand( ClientMessages::MessageTypes::CMD_DROP )
    , x_( x )
    , y_( y )
{
}

bool DropCommand::send( sf::TcpSocket& socket ) const
{
  return DropCommand::sendTwoArguments( socket, x_, y_ );
}

Json::Value DropCommand::toJson() const
{
  Json::Value root = ClientCommand::toJson();
  root[ "x" ]      = x_;
  root[ "y" ]      = y_;

  return root;
}

} // namespace MenAmongGods