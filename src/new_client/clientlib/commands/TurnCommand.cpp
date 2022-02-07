#include "TurnCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
TurnCommand::TurnCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand( ClientMessages::MessageTypes::CMD_TURN )
    , x_( x )
    , y_( y )
{
}

bool TurnCommand::send( sf::TcpSocket& socket ) const
{
  return TurnCommand::sendTwoArguments( socket, x_, y_ );
}
} // namespace MenAmongGods