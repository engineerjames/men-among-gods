#include "PickupCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
PickupCommand::PickupCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand()
    , x_( x )
    , y_( y )
{
}

void PickupCommand::send( sf::TcpSocket& socket ) const
{
  PickupCommand::sendTwoArguments( socket, x_, y_ );
}
} // namespace MenAmongGods