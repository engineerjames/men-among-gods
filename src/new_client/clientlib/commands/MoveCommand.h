#ifndef MEN_AMONG_GODS_MOVE_COMMAND_H
#define MEN_AMONG_GODS_MOVE_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class MoveCommand : public ClientCommand< CommandType, CommandType::CL_CMD_MOVE >
{
public:
  MoveCommand( std::uint16_t x, std::uint32_t y );
  virtual ~MoveCommand() = default;

  virtual void send( sf::TcpSocket& socket ) const override;

private:
  std::uint16_t x_;
  std::uint32_t y_;
};
} // namespace MenAmongGods

#endif