#include "SetUserCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>
#include <cstring>
#include <map>
#include <utility>

namespace
{

// clang-format off
const std::map< int, std::pair<int, int> > offSetToInputMap = { 
  {  0, {0, 0}  },
  {  1, {0, 13} },
  {  2, {0, 26} },
  {  3, {0, 39} },
  {  4, {0, 52} },
  {  5, {0, 65} },
  {  6, {1, 0}  },
  {  7, {1, 13} },
  {  8, {1, 26} },
  {  9, {1, 39} },
  { 10, {1, 52} },
  { 11, {1, 65} },
  { 12, {2, 0}  },
  { 13, {2, 13} },
  { 14, {2, 26} },
  { 15, {2, 39} },
  { 16, {2, 52} },
  { 17, {2, 65} }
  };
// clang-format on

} // namespace

namespace MenAmongGods
{
SetUserCommand::SetUserCommand( const std::string& playerName, const std::string& playerDescription )
    : ClientCommand( ClientMessages::MessageTypes::CMD_SETUSER )
    , playerName_( playerName )
    , playerDescription_( playerDescription )
{
}

bool SetUserCommand::send( sf::TcpSocket& socket ) const
{
  // TODO: Accomodate this when we allow for saving/loading
  // if ( ! playerData.hasPlayerDataChanged() )
  // {
  //   return false;
  // }

  std::array< std::uint8_t, 16 > buffer {};

  const constexpr int N_CHUNKS            = 18;
  const constexpr int N_BYTES_PER_PAYLOAD = 13;

  sf::Socket::Status status = sf::Socket::Status::Done;
  for ( int i = 0; i < N_CHUNKS; ++i )
  {
    buffer[ 0 ] = ClientMessages::getValue( ClientMessages::MessageTypes::CMD_SETUSER );
    buffer[ 1 ] = offSetToInputMap.at( i ).first;
    buffer[ 2 ] = offSetToInputMap.at( i ).second;

    for ( int n = 0; n < N_BYTES_PER_PAYLOAD; ++n )
    {
      if ( i >= 6 )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + offSetToInputMap.at( i ).second ];
      }
      else
      {
        buffer[ n + 3 ] = playerName_.c_str()[ n + offSetToInputMap.at( i ).second ];
      }
    }

    status = socket.send( buffer.data(), buffer.size() );
  }

  return status == sf::Socket::Status::Done;
}

Json::Value SetUserCommand::toJson() const
{
  Json::Value root            = MenAmongGods::ClientCommand::toJson();
  root[ "playerName" ]        = playerName_;
  root[ "playerDescription" ] = playerDescription_;

  return root;
}

} // namespace MenAmongGods