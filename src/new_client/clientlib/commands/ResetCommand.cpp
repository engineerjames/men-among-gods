#include "ResetCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
ResetCommand::ResetCommand()
    : ClientCommand()
{
}

void ResetCommand::send( sf::TcpSocket& socket ) const
{
  ResetCommand::sendTwoArguments( socket, 0, 0 );
}
} // namespace MenAmongGods