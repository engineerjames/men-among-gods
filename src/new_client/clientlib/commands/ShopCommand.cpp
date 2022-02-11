#include "ShopCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
ShopCommand::ShopCommand( std::uint16_t shopNumber, std::uint32_t itemNumber )
    : ClientCommand( ClientMessages::MessageTypes::CMD_SHOP )
    , shopNumber_( shopNumber )
    , itemNumber_( itemNumber )
{
}

bool ShopCommand::send( sf::TcpSocket& socket ) const
{
  return ShopCommand::sendTwoArguments( socket, shopNumber_, itemNumber_ );
}

Json::Value ShopCommand::toJson() const
{
  Json::Value root     = MenAmongGods::ClientCommand::toJson();
  root[ "shopNumber" ] = shopNumber_;
  root[ "itemNumber" ] = itemNumber_;

  return root;
}

} // namespace MenAmongGods