#include "AutoLookCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
AutoLookCommand::AutoLookCommand( std::uint32_t characterNumber )
    : ClientCommand( ClientMessages::MessageTypes::CMD_AUTOLOOK )
    , characterNumber_( characterNumber )
{
}

bool AutoLookCommand::send( sf::TcpSocket& socket ) const
{
  return AutoLookCommand::sendOneArgument( socket, characterNumber_ );
}

Json::Value AutoLookCommand::toJson() const
{
  Json::Value root          = ClientCommand::toJson();
  root[ "characterNumber" ] = characterNumber_;

  return root;
}

} // namespace MenAmongGods