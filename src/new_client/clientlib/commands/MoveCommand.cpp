#include "MoveCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
MoveCommand::MoveCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand()
    , x_( x )
    , y_( y )
{
}

bool MoveCommand::send( sf::TcpSocket& socket ) const
{
  return MoveCommand::sendTwoArguments( socket, x_, y_ );
}
} // namespace MenAmongGods