#include "PasswordCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>
#include <cstring>

namespace MenAmongGods
{
PasswordCommand::PasswordCommand( const std::string& password )
    : ClientCommand( ClientMessages::MessageTypes::PASSWD )
    , password_( password )
{
}

bool PasswordCommand::send( sf::TcpSocket& socket ) const
{
  std::array< std::uint8_t, 16 > buf {};

  buf[ 0 ] = ClientMessages::getValue( ClientMessages::MessageTypes::PASSWD );

  // Only copy 15 bytes (15 characters) into the buffer
  std::memcpy( buf.data() + 1, password_.c_str(), 15 );

  sf::Socket::Status status = socket.send( buf.data(), buf.size() );

  return status == sf::Socket::Status::Done;
}

nlohmann::json PasswordCommand::toJson() const
{
  nlohmann::json root   = MenAmongGods::ClientCommand::toJson();
  root[ "password" ] = password_;

  return root;
}

} // namespace MenAmongGods