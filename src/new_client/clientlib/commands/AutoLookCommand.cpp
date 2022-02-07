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

bool AutoLookCommand::send( sf::TcpSocket& socket ) const
{
  return AutoLookCommand::sendOneArgument( socket, characterNumber_ );
}
} // namespace MenAmongGods