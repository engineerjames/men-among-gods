#include "ModeCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
ModeCommand::ModeCommand( std::uint16_t newMode )
    : ClientCommand( ClientMessages::MessageTypes::CMD_MODE )
    , newMode_( newMode )
{
  // TODO: Update to an enum
  if ( newMode > 2 )
  {
    LOG_ERROR( "Invalid mode selected: " << newMode );
  }
}

bool ModeCommand::send( sf::TcpSocket& socket ) const
{
  return ModeCommand::sendTwoArguments( socket, newMode_, 0 );
}

Json::Value ModeCommand::toJson() const
{
  Json::Value root  = ClientCommand::toJson();
  root[ "newMode" ] = newMode_;

  return root;
}

} // namespace MenAmongGods