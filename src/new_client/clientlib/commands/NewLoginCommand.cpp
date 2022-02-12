#include "NewLoginCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
NewLoginCommand::NewLoginCommand()
    : ClientCommand( ClientMessages::MessageTypes::NEWLOGIN )
{
}

bool NewLoginCommand::send( sf::TcpSocket& socket ) const
{
  std::array< std::uint8_t, 16 > buf {};

  buf[ 0 ] = ClientMessages::getValue( ClientMessages::MessageTypes::NEWLOGIN );

  sf::Socket::Status status = socket.send( buf.data(), buf.size() );

  return status == sf::Socket::Status::Done;
}

} // namespace MenAmongGods