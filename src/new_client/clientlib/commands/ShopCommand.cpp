#include "ShopCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
ShopCommand::ShopCommand( std::uint16_t shopNumber, std::uint32_t itemNumber )
    : ClientCommand()
    , shopNumber_( shopNumber )
    , itemNumber_( itemNumber )
{
}

bool ShopCommand::send( sf::TcpSocket& socket ) const
{
  return ShopCommand::sendTwoArguments( socket, shopNumber_, itemNumber_ );
}
} // namespace MenAmongGods