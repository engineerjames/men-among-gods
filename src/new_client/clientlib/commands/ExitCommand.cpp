#include "ExitCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
ExitCommand::ExitCommand( )
    : ClientCommand()
{
}

bool ExitCommand::send( sf::TcpSocket& socket ) const
{
  return ExitCommand::sendOneArgument( socket, 0 );
}
} // namespace MenAmongGods