#include "UseCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
UseCommand::UseCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand( ClientMessages::MessageTypes::CMD_USE )
    , x_( x )
    , y_( y )
{
}

bool UseCommand::send( sf::TcpSocket& socket ) const
{
  return UseCommand::sendTwoArguments( socket, x_, y_ );
}
} // namespace MenAmongGods