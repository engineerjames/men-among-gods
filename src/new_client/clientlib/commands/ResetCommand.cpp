#include "ResetCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
ResetCommand::ResetCommand()
    : ClientCommand( ClientMessages::MessageTypes::CMD_RESET )
{
}

bool ResetCommand::send( sf::TcpSocket& socket ) const
{
  return ResetCommand::sendTwoArguments( socket, 0, 0 );
}
} // namespace MenAmongGods