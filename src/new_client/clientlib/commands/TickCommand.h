#ifndef MEN_AMONG_GODS_TICK_COMMAND_H
#define MEN_AMONG_GODS_TICK_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class TickCommand : public ClientCommand< CommandType, CommandType::CL_CMD_CTICK >
{
public:
  TickCommand( std::uint32_t tickValue );
  virtual ~TickCommand() = default;

  virtual void send( sf::TcpSocket& socket ) const override;

private:
  std::uint32_t tickValue_;
};
} // namespace MenAmongGods

#endif