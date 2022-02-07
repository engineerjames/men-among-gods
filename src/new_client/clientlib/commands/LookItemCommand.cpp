#include "LookItemCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
LookItemCommand::LookItemCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand( ClientMessages::MessageTypes::CMD_LOOK_ITEM )
    , x_( x )
    , y_( y )
{
}

bool LookItemCommand::send( sf::TcpSocket& socket ) const
{
  return LookItemCommand::sendTwoArguments( socket, x_, y_ );
}
} // namespace MenAmongGods