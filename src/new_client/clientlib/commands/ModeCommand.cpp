#include "ModeCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
ModeCommand::ModeCommand( std::uint16_t newMode )
    : ClientCommand()
    , newMode_( newMode )
{
  // TODO: Update to an enum
  if ( newMode > 2 )
  {
    std::cerr << "INVALID MODE SELECTED: " << newMode << std::endl;
  }
}

void ModeCommand::send( sf::TcpSocket& socket ) const
{
  ModeCommand::sendTwoArguments( socket, newMode_, 0 );
}
} // namespace MenAmongGods