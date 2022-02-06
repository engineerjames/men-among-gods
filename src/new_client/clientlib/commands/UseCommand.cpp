#include "UseCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
UseCommand::UseCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand()
    , x_( x )
    , y_( y )
{
}

void UseCommand::send( sf::TcpSocket& socket ) const
{
  UseCommand::sendTwoArguments( socket, x_, y_ );
}
} // namespace MenAmongGods