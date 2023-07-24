#include "PickupCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
PickupCommand::PickupCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand( ClientMessages::MessageTypes::CMD_PICKUP )
    , x_( x )
    , y_( y )
{
}

bool PickupCommand::send( sf::TcpSocket& socket ) const
{
  return PickupCommand::sendTwoArguments( socket, x_, y_ );
}

nlohmann::json PickupCommand::toJson() const
{
  nlohmann::json root = MenAmongGods::ClientCommand::toJson();
  root[ "x" ]      = x_;
  root[ "y" ]      = y_;

  return root;
}

} // namespace MenAmongGods