#ifndef MEN_AMONG_GODS_DROP_COMMAND_H
#define MEN_AMONG_GODS_DROP_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class DropCommand : public ClientCommand< CommandType, CommandType::CL_CMD_DROP >
{
public:
  DropCommand( std::uint16_t x, std::uint32_t y );
  virtual ~DropCommand() = default;

  virtual void send( sf::TcpSocket& socket ) const override;

private:
  std::uint16_t x_;
  std::uint32_t y_;
};
} // namespace MenAmongGods

#endif