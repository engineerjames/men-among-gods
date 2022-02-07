#ifndef MEN_AMONG_GODS_SKILL_COMMAND_H
#define MEN_AMONG_GODS_SKILL_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class SkillCommand : public ClientCommand< CommandType, CommandType::CL_CMD_INV >
{
public:
  SkillCommand( std::uint32_t x, std::uint32_t selectedCharacter, std::uint32_t y );
  virtual ~SkillCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::uint32_t x_;
  std::uint32_t selectedCharacter_;
  std::uint32_t y_;
};
} // namespace MenAmongGods

#endif