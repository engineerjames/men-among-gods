#include "SayCommand.h"

#include <SFML/Network.hpp>

#include <cstdint>
#include <cstring>
#include <map>

namespace
{

static const constexpr unsigned int CMD_INPUT1_OFFSET = 0;
static const constexpr unsigned int CMD_INPUT2_OFFSET = 15;
static const constexpr unsigned int CMD_INPUT3_OFFSET = 30;
static const constexpr unsigned int CMD_INPUT4_OFFSET = 45;
static const constexpr unsigned int CMD_INPUT5_OFFSET = 60;
static const constexpr unsigned int CMD_INPUT6_OFFSET = 75;
static const constexpr unsigned int CMD_INPUT7_OFFSET = 90;
static const constexpr unsigned int CMD_INPUT8_OFFSET = 105;

static const constexpr unsigned int STRING_BUFFER_SIZE = 250;

static const constexpr unsigned int TCP_BUFFER_SIZE = 16;

// clang-format off
const std::map< ClientMessages::MessageTypes, unsigned int > offSetToInputMap = { 
  { ClientMessages::MessageTypes::CMD_INPUT1, CMD_INPUT1_OFFSET },
  { ClientMessages::MessageTypes::CMD_INPUT2, CMD_INPUT2_OFFSET },
  { ClientMessages::MessageTypes::CMD_INPUT3, CMD_INPUT3_OFFSET },
  { ClientMessages::MessageTypes::CMD_INPUT4, CMD_INPUT4_OFFSET },
  { ClientMessages::MessageTypes::CMD_INPUT5, CMD_INPUT5_OFFSET },
  { ClientMessages::MessageTypes::CMD_INPUT6, CMD_INPUT6_OFFSET },
  { ClientMessages::MessageTypes::CMD_INPUT7, CMD_INPUT7_OFFSET },
  { ClientMessages::MessageTypes::CMD_INPUT8, CMD_INPUT8_OFFSET } 
  };
// clang-format on
} // namespace

namespace MenAmongGods
{
SayCommand::SayCommand( const std::string& statement )
    : ClientCommand( ClientMessages::MessageTypes::EMPTY )
    , statement_( statement )
{
}

bool SayCommand::sendPartialMessage( sf::TcpSocket& socket, const std::array< char, STRING_BUFFER_SIZE >& stringBuffer,
                                     ClientMessages::MessageTypes inputType ) const
{
  std::size_t                         bytesSent = 0;
  std::array< char, TCP_BUFFER_SIZE > buf {};

  buf[ 0 ] = static_cast< unsigned char >( inputType );
  for ( unsigned int n = 0; n < ( TCP_BUFFER_SIZE - 1 ); n++ )
  {
    const unsigned int bufferIdx = n + offSetToInputMap.at( inputType );
    buf[ n + 1 ]                 = stringBuffer[ bufferIdx ];
  }

  sf::Socket::Status status = sf::Socket::Status::Done;
  while ( bytesSent != TCP_BUFFER_SIZE )
  {
    status = socket.send( buf.data(), buf.size(), bytesSent );
  }

  return status == sf::Socket::Status::Done;
}

// For the "say" command, we need to do things a little differently.
// Essentially, we chop up the input string into 16 byte chunks (with
// the first byte devoted to the CMD_INPUT#) each time.  We then
// send each piece in order.
bool SayCommand::send( sf::TcpSocket& socket ) const
{
  // First, copy the source string into a local buffer that guarantees
  // we don't end up reading beyond the length of the string.  The current
  // logic allows for ~120 characters, so we'll do 250 just to be safe.
  std::array< char, STRING_BUFFER_SIZE > stringBuffer {};
  std::strncpy( stringBuffer.data(), statement_.c_str(), statement_.length() );

  bool inputSent = true;

  inputSent &= sendPartialMessage( socket, stringBuffer, ClientMessages::MessageTypes::CMD_INPUT1 );
  inputSent &= sendPartialMessage( socket, stringBuffer, ClientMessages::MessageTypes::CMD_INPUT2 );
  inputSent &= sendPartialMessage( socket, stringBuffer, ClientMessages::MessageTypes::CMD_INPUT3 );
  inputSent &= sendPartialMessage( socket, stringBuffer, ClientMessages::MessageTypes::CMD_INPUT4 );
  inputSent &= sendPartialMessage( socket, stringBuffer, ClientMessages::MessageTypes::CMD_INPUT5 );
  inputSent &= sendPartialMessage( socket, stringBuffer, ClientMessages::MessageTypes::CMD_INPUT6 );
  inputSent &= sendPartialMessage( socket, stringBuffer, ClientMessages::MessageTypes::CMD_INPUT7 );
  inputSent &= sendPartialMessage( socket, stringBuffer, ClientMessages::MessageTypes::CMD_INPUT8 );

  LOG_DEBUG_OBJ( *this, "Successful send: " << inputSent );

  return inputSent;
}

Json::Value SayCommand::toJson() const
{
  Json::Value root    = MenAmongGods::ClientCommand::toJson();
  root[ "statement" ] = statement_;

  return root;
}

} // namespace MenAmongGods