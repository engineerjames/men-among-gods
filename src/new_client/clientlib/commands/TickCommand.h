#ifndef MEN_AMONG_GODS_TICK_COMMAND_H
#define MEN_AMONG_GODS_TICK_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class TickCommand : public ClientCommand
{
public:
  TickCommand( std::uint32_t tickValue );
  virtual ~TickCommand() = default;

  virtual bool        send( sf::TcpSocket& socket ) const override;
  virtual Json::Value toJson() const override;

private:
  std::uint32_t tickValue_;
};
} // namespace MenAmongGods

#endif