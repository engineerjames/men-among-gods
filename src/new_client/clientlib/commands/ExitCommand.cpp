#include "ExitCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
ExitCommand::ExitCommand( )
    : ClientCommand()
{
}

void ExitCommand::send( sf::TcpSocket& socket ) const
{
  ExitCommand::sendOneArgument( socket, 0 );
}
} // namespace MenAmongGods