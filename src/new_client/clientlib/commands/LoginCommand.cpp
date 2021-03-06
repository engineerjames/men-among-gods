#include "LoginCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
LoginCommand::LoginCommand( std::uint32_t userNumber, std::uint32_t password1, std::uint32_t password2 )
    : ClientCommand( ClientMessages::MessageTypes::LOGIN )
    , userNumber_( userNumber )
    , password1_( password1 )
    , password2_( password2 )
{
}

bool LoginCommand::send( sf::TcpSocket& socket ) const
{
  std::array< std::uint8_t, 16 > buf {};

  buf[ 0 ] = ClientMessages::getValue( ClientMessages::MessageTypes::LOGIN );

  std::memcpy( buf.data() + 1, &userNumber_, sizeof( std::uint32_t ) );
  std::memcpy( buf.data() + 5, &password1_, sizeof( std::uint32_t ) );
  std::memcpy( buf.data() + 9, &password2_, sizeof( std::uint32_t ) );

  sf::Socket::Status status = socket.send( buf.data(), buf.size() );

  return status == sf::Socket::Status::Done;
}

} // namespace MenAmongGods