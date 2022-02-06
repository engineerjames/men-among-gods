#include "TurnCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
TurnCommand::TurnCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand()
    , x_( x )
    , y_( y )
{
}

void TurnCommand::send( sf::TcpSocket& socket ) const
{
  TurnCommand::sendTwoArguments( socket, x_, y_ );
}
} // namespace MenAmongGods