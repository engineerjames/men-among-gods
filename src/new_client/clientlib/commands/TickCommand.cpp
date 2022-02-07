#include "TickCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
TickCommand::TickCommand( std::uint32_t tickValue )
    : ClientCommand( ClientMessages::MessageTypes::CMD_CTICK )
    , tickValue_( tickValue )
{
}

bool TickCommand::send( sf::TcpSocket& socket ) const
{
  return TickCommand::sendOneArgument( socket, tickValue_ );
}
} // namespace MenAmongGods