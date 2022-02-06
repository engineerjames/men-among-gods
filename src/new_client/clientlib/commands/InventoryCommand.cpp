#include "InventoryCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
InventoryCommand::InventoryCommand( std::uint32_t x, std::uint32_t y, std::uint32_t selectedCharacter )
    : ClientCommand()
    , x_( x )
    , y_( y )
    , selectedCharacter_( selectedCharacter )
{
}

void InventoryCommand::send( sf::TcpSocket& socket ) const
{
  InventoryCommand::sendThreeArguments( socket, x_, y_, selectedCharacter_ );
}
} // namespace MenAmongGods