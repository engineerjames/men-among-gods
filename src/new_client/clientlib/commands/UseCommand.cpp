#include "UseCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
UseCommand::UseCommand( std::uint16_t x, std::uint32_t y )
    : ClientCommand( ClientMessages::MessageTypes::CMD_USE )
    , x_( x )
    , y_( y )
{
}

bool UseCommand::send( sf::TcpSocket& socket ) const
{
  return UseCommand::sendTwoArguments( socket, x_, y_ );
}

nlohmann::json UseCommand::toJson() const
{
  nlohmann::json root = MenAmongGods::ClientCommand::toJson();
  root[ "x" ]      = x_;
  root[ "y" ]      = y_;

  return root;
}

} // namespace MenAmongGods