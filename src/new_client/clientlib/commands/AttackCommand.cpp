#include "AttackCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
AttackCommand::AttackCommand( std::uint32_t characterNumber )
    : ClientCommand()
    , characterNumber_( characterNumber )
{
}

void AttackCommand::send( sf::TcpSocket& socket ) const
{
  AttackCommand::sendOneArgument( socket, characterNumber_ );
}
} // namespace MenAmongGods