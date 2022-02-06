#include "DropCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
DropCommand::DropCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand()
    , x_( x )
    , y_( y )
{
}

void DropCommand::send( sf::TcpSocket& socket ) const
{
  DropCommand::sendTwoArguments( socket, x_, y_ );
}
} // namespace MenAmongGods