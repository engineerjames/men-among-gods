#include "InventoryLookCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
InventoryLookCommand::InventoryLookCommand( std::uint32_t x, std::uint32_t selectedCharacter )
    : ClientCommand( ClientMessages::MessageTypes::CMD_INV_LOOK )
    , x_( x )
    , selectedCharacter_( selectedCharacter )
{
}

bool InventoryLookCommand::send( sf::TcpSocket& socket ) const
{
  return InventoryLookCommand::sendThreeArguments( socket, x_, 0, selectedCharacter_ );
}

nlohmann::json InventoryLookCommand::toJson() const
{
  nlohmann::json root            = ClientCommand::toJson();
  root[ "x" ]                 = x_;
  root[ "selectedCharacter" ] = selectedCharacter_;

  return root;
}

} // namespace MenAmongGods