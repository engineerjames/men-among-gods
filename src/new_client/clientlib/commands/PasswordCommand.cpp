#include "PasswordCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>
#include <iostream>

namespace MenAmongGods
{
PasswordCommand::PasswordCommand( std::uint32_t passwordHash, std::uint32_t version, std::uint32_t raceAndSex )
    : ClientCommand( ClientMessages::MessageTypes::PASSWD )
    , passwordHash_( passwordHash )
    , version_( version )
    , raceAndSex_( raceAndSex )
{
}

bool PasswordCommand::send( sf::TcpSocket& socket ) const
{
  std::array< std::uint8_t, 16 > buf {};

  buf[ 0 ]                               = ClientMessages::getValue( ClientMessages::MessageTypes::PASSWD );
  *( unsigned long* ) ( buf.data() + 1 ) = passwordHash_;
  *( unsigned long* ) ( buf.data() + 5 ) = version_;
  *( unsigned long* ) ( buf.data() + 9 ) = raceAndSex_;
  std::cerr << "Sending CL_PASSWORD...\n";
  std::cerr << "tmp: " << passwordHash_ << std::endl;
  std::cerr << "VERSION: " << version_ << std::endl;
  std::cerr << "OkeyRaceInt: " << raceAndSex_;

  sf::Socket::Status status = socket.send( buf.data(), buf.size() );

  return status == sf::Socket::Status::Done;
}
} // namespace MenAmongGods