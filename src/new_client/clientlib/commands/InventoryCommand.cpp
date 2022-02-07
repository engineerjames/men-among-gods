#include "InventoryCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
InventoryCommand::InventoryCommand( std::uint32_t x, std::uint32_t y, std::uint32_t selectedCharacter )
    : ClientCommand( ClientMessages::MessageTypes::CMD_INV )
    , x_( x )
    , y_( y )
    , selectedCharacter_( selectedCharacter )
{
}

bool InventoryCommand::send( sf::TcpSocket& socket ) const
{
  return InventoryCommand::sendThreeArguments( socket, x_, y_, selectedCharacter_ );
}
} // namespace MenAmongGods