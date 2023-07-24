#include "StatCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
StatCommand::StatCommand( std::uint16_t statNumber, std::uint32_t raiseNTimes )
    : ClientCommand( ClientMessages::MessageTypes::CMD_STAT )
    , statNumber_( statNumber )
    , raiseNTimes_( raiseNTimes )
{
}

bool StatCommand::send( sf::TcpSocket& socket ) const
{
  return StatCommand::sendTwoArguments( socket, statNumber_, raiseNTimes_ );
}

nlohmann::json StatCommand::toJson() const
{
  nlohmann::json root      = MenAmongGods::ClientCommand::toJson();
  root[ "statNumber" ]  = statNumber_;
  root[ "raiseNTimes" ] = raiseNTimes_;

  return root;
}

} // namespace MenAmongGods