#include "StatCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
StatCommand::StatCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand()
    , x_( x )
    , y_( y )
{
}

void StatCommand::send( sf::TcpSocket& socket ) const
{
  StatCommand::sendTwoArguments( socket, x_, y_ );
}
} // namespace MenAmongGods