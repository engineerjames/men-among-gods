#include "GiveCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
GiveCommand::GiveCommand( std::uint32_t characterNumber )
    : ClientCommand()
    , characterNumber_( characterNumber )
{
}

bool GiveCommand::send( sf::TcpSocket& socket ) const
{
  return GiveCommand::sendOneArgument( socket, characterNumber_ );
}
} // namespace MenAmongGods