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
  { CommandType::CL_CMD_INPUT1, 15 },
  { CommandType::CL_CMD_INPUT1, 30 },
  { CommandType::CL_CMD_INPUT1, 45 },
  { CommandType::CL_CMD_INPUT1, 60 },
  { CommandType::CL_CMD_INPUT1, 75 },
  { CommandType::CL_CMD_INPUT1, 90 },
  { CommandType::CL_CMD_INPUT1, 105 } 
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

void SayCommand::sendPartialMessage( sf::TcpSocket& socket, const std::array< char, 250 >& stringBuffer, CommandType inputType ) const
{
  std::size_t bytesSent = 0;
  char        buf[ 16 ] {};

  buf[ 0 ] = static_cast< unsigned char >( inputType );
  for ( int n = 0; n < 15; n++ )
  {
    buf[ n + 1 ] = stringBuffer[ n + offSetToInputMap.at( inputType ) ];
  }

  while ( bytesSent != 16 )
  {
    socket.send( buf, sizeof( buf ), bytesSent );
  }
}

// For the "say" command, we need to do things a little differently.
// Essentially, we chop up the input string into 16 byte chunks (with
// the first byte devoted to the CL_CMD_INPUT#) each time.  We then
// send each piece in order.
void SayCommand::send( sf::TcpSocket& socket ) const
{
  // First, copy the source string into a local buffer that guarantees
  // we don't end up reading beyond the length of the string.  The current
  // logic allows for ~120 characters, so we'll do 250 just to be safe.
  std::array< char, 250 > stringBuffer {};
  std::strcpy( stringBuffer.data(), statement_.c_str() );

  sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT1 );
  sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT2 );
  sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT3 );
  sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT4 );
  sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT5 );
  sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT6 );
  sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT7 );
  sendPartialMessage( socket, stringBuffer, CommandType::CL_CMD_INPUT8 );
}
} // namespace MenAmongGods