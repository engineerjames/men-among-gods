#include "TurnCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
TurnCommand::TurnCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand( ClientMessages::MessageTypes::CMD_TURN )
    , x_( x )
    , y_( y )
{
}

bool TurnCommand::send( sf::TcpSocket& socket ) const
{
  return TurnCommand::sendTwoArguments( socket, x_, y_ );
}

nlohmann::json TurnCommand::toJson() const
{
  nlohmann::json root = MenAmongGods::ClientCommand::toJson();
  root[ "x" ]      = x_;
  root[ "y" ]      = y_;

  return root;
}

} // namespace MenAmongGods