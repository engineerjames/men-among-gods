#ifndef MEN_AMONG_GODS_MODE_COMMAND_H
#define MEN_AMONG_GODS_MODE_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class ModeCommand : public ClientCommand< CommandType, CommandType::CL_CMD_MODE >
{
public:
  ModeCommand( std::uint16_t newMode );
  virtual ~ModeCommand() = default;

  virtual void send( sf::TcpSocket& socket ) const override;

private:
  std::uint16_t newMode_;
};
} // namespace MenAmongGods

#endif