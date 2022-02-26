#include "ChallengeCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>
#include <cstring>

#include "Logger.h"

namespace MenAmongGods
{
ChallengeCommand::ChallengeCommand( std::uint32_t challengeHash, std::uint32_t version, std::int32_t raceAndSex )
    : ClientCommand( ClientMessages::MessageTypes::CHALLENGE )
    , challengeHash_( challengeHash )
    , version_( version )
    , raceAndSex_( raceAndSex )
{
}

bool ChallengeCommand::send( sf::TcpSocket& socket ) const
{
  std::array< std::uint8_t, 16 > buf {};

  buf[ 0 ]                               = ClientMessages::getValue( ClientMessages::MessageTypes::CHALLENGE );
  // *( std::uint32_t* ) ( buf.data() + 1 ) = challengeHash_;
  // *( std::uint32_t* ) ( buf.data() + 5 ) = version_;
  // *( std::uint32_t* ) ( buf.data() + 9 ) = raceAndSex_;

  std::memcpy( buf.data() + 1, &challengeHash_, sizeof( challengeHash_ ) );
  std::memcpy( buf.data() + 5, &version_, sizeof( version_ ) );
  std::memcpy( buf.data() + 9, &raceAndSex_, sizeof( version_ ) );

  LOG_DEBUG( "Sending CL_CHALLENGE - tmp: " << challengeHash_ << "VERSION: " << version_ << "OkeyRaceInt: " << raceAndSex_ );

  sf::Socket::Status status = socket.send( buf.data(), buf.size() );

  return status == sf::Socket::Status::Done;
}

Json::Value ChallengeCommand::toJson() const
{
  Json::Value root        = ClientCommand::toJson();
  root[ "challengeHash" ] = challengeHash_;
  root[ "version" ]       = version_;
  root[ "raceAndSex" ]    = raceAndSex_;

  return root;
}

} // namespace MenAmongGods