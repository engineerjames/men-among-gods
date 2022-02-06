#include "AutoLookCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
AutoLookCommand::AutoLookCommand( std::uint32_t characterNumber )
    : ClientCommand()
    , characterNumber_( characterNumber )
{
}

void AutoLookCommand::send( sf::TcpSocket& socket ) const
{
  AutoLookCommand::sendOneArgument( socket, characterNumber_ );
}
} // namespace MenAmongGods