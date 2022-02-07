#ifndef MEN_AMONG_GODS_RESET_COMMAND_H
#define MEN_AMONG_GODS_RESET_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class ResetCommand : public ClientCommand< CommandType, CommandType::CL_CMD_RESET >
{
public:
  ResetCommand( );
  virtual ~ResetCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  // Nothing for now
};
} // namespace MenAmongGods

#endif