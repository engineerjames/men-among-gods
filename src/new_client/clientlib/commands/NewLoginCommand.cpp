#include "NewLoginCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>
#include <iostream>

namespace MenAmongGods
{
NewLoginCommand::NewLoginCommand( std::uint32_t newloginHash, std::uint32_t version, std::uint32_t raceAndSex )
    : ClientCommand( ClientMessages::MessageTypes::NEWLOGIN )
    , newloginHash_( newloginHash )
    , version_( version )
    , raceAndSex_( raceAndSex )
{
}

bool NewLoginCommand::send( sf::TcpSocket& socket ) const
{
  std::array< std::uint8_t, 16 > buf {};

  buf[ 0 ]                               = ClientMessages::getValue( ClientMessages::MessageTypes::NEWLOGIN );
  *( unsigned long* ) ( buf.data() + 1 ) = newloginHash_;
  *( unsigned long* ) ( buf.data() + 5 ) = version_;
  *( unsigned long* ) ( buf.data() + 9 ) = raceAndSex_;
  std::cerr << "Sending CL_NEWLOGIN...\n";
  std::cerr << "tmp: " << newloginHash_ << std::endl;
  std::cerr << "VERSION: " << version_ << std::endl;
  std::cerr << "OkeyRaceInt: " << raceAndSex_;

  sf::Socket::Status status = socket.send( buf.data(), buf.size() );

  return status == sf::Socket::Status::Done;
}
} // namespace MenAmongGods