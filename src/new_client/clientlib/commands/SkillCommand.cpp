#include "SkillCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
SkillCommand::SkillCommand( std::uint32_t x, std::uint32_t selectedCharacter, std::uint32_t y )
    : ClientCommand()
    , x_( x )
    , selectedCharacter_( selectedCharacter )
    , y_( y )
{
}

void SkillCommand::send( sf::TcpSocket& socket ) const
{
  SkillCommand::sendThreeArguments( socket, x_, selectedCharacter_, y_ );
}
} // namespace MenAmongGods