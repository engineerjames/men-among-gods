#include "LookItemCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
LookItemCommand::LookItemCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand()
    , x_( x )
    , y_( y )
{
}

void LookItemCommand::send( sf::TcpSocket& socket ) const
{
  LookItemCommand::sendTwoArguments( socket, x_, y_ );
}
} // namespace MenAmongGods