#include "SkillCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
SkillCommand::SkillCommand( std::uint32_t x, std::uint32_t selectedCharacter, std::uint32_t y )
    : ClientCommand( ClientMessages::MessageTypes::CMD_INV )
    , x_( x )
    , selectedCharacter_( selectedCharacter )
    , y_( y )
{
}

bool SkillCommand::send( sf::TcpSocket& socket ) const
{
  return SkillCommand::sendThreeArguments( socket, x_, selectedCharacter_, y_ );
}
} // namespace MenAmongGods