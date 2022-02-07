#include "ResetCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
ResetCommand::ResetCommand()
    : ClientCommand()
{
}

bool ResetCommand::send( sf::TcpSocket& socket ) const
{
  return ResetCommand::sendTwoArguments( socket, 0, 0 );
}
} // namespace MenAmongGods