#ifndef MEN_AMONG_GODS_EXIT_COMMAND_H
#define MEN_AMONG_GODS_EXIT_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class ExitCommand : public ClientCommand< CommandType, CommandType::CL_CMD_EXIT >
{
public:
  ExitCommand();
  virtual ~ExitCommand() = default;

  virtual void send( sf::TcpSocket& socket ) const override;

private:
  // Nothing for now
};
} // namespace MenAmongGods

#endif