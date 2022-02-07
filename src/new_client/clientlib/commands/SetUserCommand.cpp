#include "SetUserCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>
#include <cstring>
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
    : ClientCommand()
    , playerName_( playerName )
    , playerDescription_( playerDescription )
{
}

bool SetUserCommand::send( sf::TcpSocket& ) const
{
  return false;
}
} // namespace MenAmongGods