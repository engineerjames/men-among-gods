#include "LookCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
LookCommand::LookCommand( std::uint32_t characterNumber )
    : ClientCommand()
    , characterNumber_( characterNumber )
{
}

void LookCommand::send( sf::TcpSocket& socket ) const
{
  LookCommand::sendOneArgument( socket, characterNumber_ );
}
} // namespace MenAmongGods