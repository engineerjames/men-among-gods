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

void GiveCommand::send( sf::TcpSocket& socket ) const
{
  GiveCommand::sendOneArgument( socket, characterNumber_ );
}
} // namespace MenAmongGods