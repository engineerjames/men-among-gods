#include "GiveCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
GiveCommand::GiveCommand( std::uint32_t characterNumber )
    : ClientCommand( ClientMessages::MessageTypes::CMD_GIVE )
    , characterNumber_( characterNumber )
{
}

bool GiveCommand::send( sf::TcpSocket& socket ) const
{
  return GiveCommand::sendOneArgument( socket, characterNumber_ );
}

nlohmann::json GiveCommand::toJson() const
{
  nlohmann::json root          = ClientCommand::toJson();
  root[ "characterNumber" ] = characterNumber_;

  return root;
}

} // namespace MenAmongGods