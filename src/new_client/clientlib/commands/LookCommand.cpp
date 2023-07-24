#include "LookCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
LookCommand::LookCommand( std::uint32_t characterNumber )
    : ClientCommand( ClientMessages::MessageTypes::CMD_LOOK )
    , characterNumber_( characterNumber )
{
}

bool LookCommand::send( sf::TcpSocket& socket ) const
{
  return LookCommand::sendOneArgument( socket, characterNumber_ );
}

nlohmann::json LookCommand::toJson() const
{
  nlohmann::json root          = ClientCommand::toJson();
  root[ "characterNumber" ] = characterNumber_;

  return root;
}

} // namespace MenAmongGods