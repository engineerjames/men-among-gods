#ifndef MEN_AMONG_GODS_ATTACK_COMMAND_H
#define MEN_AMONG_GODS_ATTACK_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class AttackCommand : public ClientCommand
{
public:
  AttackCommand( std::uint32_t characterNumber );
  virtual ~AttackCommand() = default;

  virtual bool        send( sf::TcpSocket& socket ) const override;
  virtual nlohmann::json toJson() const override;

private:
  std::uint32_t characterNumber_;
};
} // namespace MenAmongGods

#endif