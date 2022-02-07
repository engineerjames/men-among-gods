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
} // namespace MenAmongGods