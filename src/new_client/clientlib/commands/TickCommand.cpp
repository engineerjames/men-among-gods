#include "TickCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
TickCommand::TickCommand( std::uint32_t tickValue )
    : ClientCommand()
    , tickValue_( tickValue )
{
}

void TickCommand::send( sf::TcpSocket& socket ) const
{
  TickCommand::sendOneArgument( socket, tickValue_ );
}
} // namespace MenAmongGods