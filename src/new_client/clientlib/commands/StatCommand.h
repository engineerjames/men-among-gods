#ifndef MEN_AMONG_GODS_STAT_COMMAND_H
#define MEN_AMONG_GODS_STAT_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class StatCommand : public ClientCommand
{
public:
  StatCommand( std::uint16_t statNumber, std::uint32_t raiseNTimes );
  virtual ~StatCommand() = default;

  virtual bool        send( sf::TcpSocket& socket ) const override;
  virtual nlohmann::json toJson() const override;

private:
  std::uint16_t statNumber_;
  std::uint32_t raiseNTimes_;
};
} // namespace MenAmongGods

#endif