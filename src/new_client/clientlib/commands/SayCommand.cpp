#include "SayCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>
#include <cstring>
#include <map>

namespace
{
// clang-format off
std::map< CommandType, unsigned int > offSetToInputMap = { 
  { CommandType::CL_CMD_INPUT1, 0 },
  { CommandType::CL_CMD_INPUT2, 15 },
  { CommandType::CL_CMD_INPUT3, 30 },
  { CommandType::CL_CMD_INPUT4, 45 },
  { CommandType::CL_CMD_INPUT5, 60 },
  { CommandType::CL_CMD_INPUT6, 75 },
  { CommandType::CL_CMD_INPUT7, 90 },
  { CommandType::CL_CMD_INPUT8, 105 } 
  };
// clang-format on
} // namespace

namespace MenAmongGods
{
SayCommand::SayCommand( const std::string& statement )
    : ClientCommand()
    , statement_( statement )
{
}

bool SayCommand::sendPartialMessage( sf::TcpSocket& socket, const std::array< char, 250 >& stringBuffer, CommandType inputType ) const
{
  std::size_t bytesSent = 0;
  char        buf[ 16 ] {};

  buf[ 0 ] = static_cast< unsigned char >( inputType );
  for ( int n = 0; n < 15; n++ )
  {
    buf[ n + 1 ] = stringBuffer[ n + offSetToInputMap.at( inputType ) ];
  }

  sf::Socket::Status status = sf::Socket::Status::Done;
  while ( bytesSent != 16 )
  {
    status = socket.send( buf, sizeof( buf ), bytesSent );
  }

  return status == sf::Socket::Status::Done;
}

// For the "say" command, we need to do things a little differently.
// Essentially, we chop up the input string into 16 byte chunks (with
// the first byte devoted to the CL_CMD_INPUT#) each time.  We then
// send each piece in order.
bool SayCommand::send( sf::TcpSocket& socket ) const
{
  // First, copy the source string into a local buffer that guarantees
  // we don't end up reading beyond the length of the string.  The current
  // logic allows for ~120 characters, so we'll do 250 just to be safe.
  std::array< char, 250 > stringBuffer {};
  std::strcpy( stringBuffer.data(), statement_.c_str() );

  bool inputSent = true;

  inputSent &= sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT1 );
  inputSent &= sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT2 );
  inputSent &= sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT3 );
  inputSent &= sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT4 );
  inputSent &= sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT5 );
  inputSent &= sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT6 );
  inputSent &= sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT7 );
  inputSent &= sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT8 );

  return inputSent;
}
} // namespace MenAmongGods