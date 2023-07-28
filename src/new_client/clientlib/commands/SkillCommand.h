#ifndef MEN_AMONG_GODS_SKILL_COMMAND_H
#define MEN_AMONG_GODS_SKILL_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class SkillCommand : public ClientCommand
{
public:
  SkillCommand( std::uint32_t skillNumber, std::uint32_t selectedCharacter, std::uint32_t baseModifierAttribute );
  virtual ~SkillCommand() = default;

  virtual bool        send( sf::TcpSocket& socket ) const override;
  virtual nlohmann::json toJson() const override;

private:
  std::uint32_t skillNumber_;
  std::uint32_t selectedCharacter_;
  std::uint32_t baseModifierAttribute_;
};
} // namespace MenAmongGods

#endif