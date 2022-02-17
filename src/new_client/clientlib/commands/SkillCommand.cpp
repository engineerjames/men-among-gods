#include "SkillCommand.h"

#include <SFML/Network.hpp>
#include <cstdint>

namespace MenAmongGods
{
SkillCommand::SkillCommand( std::uint32_t skillNumber, std::uint32_t selectedCharacter, std::uint32_t baseModifierAttribute )
    : ClientCommand( ClientMessages::MessageTypes::CMD_SKILL )
    , skillNumber_( skillNumber )
    , selectedCharacter_( selectedCharacter )
    , baseModifierAttribute_( baseModifierAttribute )
{
}

bool SkillCommand::send( sf::TcpSocket& socket ) const
{
  return SkillCommand::sendThreeArguments( socket, skillNumber_, selectedCharacter_, baseModifierAttribute_ );
}

Json::Value SkillCommand::toJson() const
{
  Json::Value root                = MenAmongGods::ClientCommand::toJson();
  root[ "skillNumber" ]           = skillNumber_;
  root[ "baseModifierAttribute" ] = baseModifierAttribute_;
  root[ "selectedCharacter" ]     = selectedCharacter_;

  return root;
}

} // namespace MenAmongGods