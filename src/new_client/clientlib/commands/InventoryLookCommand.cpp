#include "InventoryLookCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
InventoryLookCommand::InventoryLookCommand( std::uint32_t x, std::uint32_t selectedCharacter )
    : ClientCommand()
    , x_( x )
    , selectedCharacter_( selectedCharacter )
{
}

bool InventoryLookCommand::send( sf::TcpSocket& socket ) const
{
  return InventoryLookCommand::sendThreeArguments( socket, x_, 0, selectedCharacter_ );
}
} // namespace MenAmongGods