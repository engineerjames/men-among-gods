#ifndef MEN_AMONG_GODS_LOOK_COMMAND_H
#define MEN_AMONG_GODS_LOOK_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class LookCommand : public ClientCommand< CommandType, CommandType::CL_CMD_LOOK >
{
public:
  LookCommand( std::uint32_t characterNumber );
  virtual ~LookCommand() = default;

  virtual void send( sf::TcpSocket& socket ) const override;

private:
  std::uint32_t characterNumber_;
};
} // namespace MenAmongGods

#endif