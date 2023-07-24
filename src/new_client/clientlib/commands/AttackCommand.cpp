#include "AttackCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
AttackCommand::AttackCommand( std::uint32_t characterNumber )
    : ClientCommand( ClientMessages::MessageTypes::CMD_ATTACK )
    , characterNumber_( characterNumber )
{
}

bool AttackCommand::send( sf::TcpSocket& socket ) const
{
  return AttackCommand::sendOneArgument( socket, characterNumber_ );
}

nlohmann::json AttackCommand::toJson() const
{
  nlohmann::json root          = ClientCommand::toJson();
  root[ "characterNumber" ] = characterNumber_;

  return root;
}

} // namespace MenAmongGods