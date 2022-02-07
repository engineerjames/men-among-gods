#include "SetUserCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>

namespace
{
// clang-format off
std::map< ClientMessages::MessageTypes, unsigned int > offSetToInputMap = { 
  { ClientMessages::MessageTypes::CMD_INPUT1, 0 },
  { ClientMessages::MessageTypes::CMD_INPUT2, 15 },
  { ClientMessages::MessageTypes::CMD_INPUT3, 30 },
  { ClientMessages::MessageTypes::CMD_INPUT4, 45 },
  { ClientMessages::MessageTypes::CMD_INPUT5, 60 },
  { ClientMessages::MessageTypes::CMD_INPUT6, 75 },
  { ClientMessages::MessageTypes::CMD_INPUT7, 90 },
  { ClientMessages::MessageTypes::CMD_INPUT8, 105 } 
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
  int                            state = 0;
  std::array< std::uint8_t, 16 > buffer {};
  int                            n {};
  bool                           completedTransfer = false;

  // TODO: Refactor this so the logic is easier to follow.
  while ( ! completedTransfer )
  {
    buffer[ 0 ] = ClientMessages::getValue( ClientMessages::MessageTypes::CMD_SETUSER );

    switch ( state )
    {
    case 0:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 0;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerName_.c_str()[ n ];
      }
      std::cerr << "Transfering user data...";
      break;
    case 1:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 13;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerName_.c_str()[ n + 13 ];
      }
      break;
    case 2:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 26;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerName_.c_str()[ n + 26 ];
      }
      break;
    case 3:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 39;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerName_.c_str()[ n + 39 ];
      }
      break;
    case 4:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 52;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerName_.c_str()[ n + 52 ];
      }
      break;
    case 5:
      buffer[ 1 ] = 0;
      buffer[ 2 ] = 65;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerName_.c_str()[ n + 65 ];
      }
      break;

    case 6:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 0;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n ];
      }
      break;
    case 7:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 13;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 13 ];
      }
      break;
    case 8:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 26;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 26 ];
      }
      break;
    case 9:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 39;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 39 ];
      }
      break;
    case 10:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 52;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 52 ];
      }
      break;
    case 11:
      buffer[ 1 ] = 1;
      buffer[ 2 ] = 65;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 65 ];
      }
      break;

    case 12:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 0;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 78 ];
      }
      break;
    case 13:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 13;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 91 ];
      }
      break;
    case 14:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 26;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 104 ];
      }
      break;
    case 15:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 39;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 117 ];
      }
      break;
    case 16:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 52;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 130 ];
      }
      break;
    case 17:
      buffer[ 1 ] = 2;
      buffer[ 2 ] = 65;
      for ( n = 0; n < 13; n++ )
      {
        buffer[ n + 3 ] = playerDescription_.c_str()[ n + 143 ];
      }
      std::cerr << "Transfer done.\n";
      completedTransfer = true;
      break;
    default:
      std::cerr << "Invalid state!" << std::endl;
      return false;
    }

    socket.send( buffer.data(), buffer.size() );
    state++;
  }

  return completedTransfer;
}
} // namespace MenAmongGods