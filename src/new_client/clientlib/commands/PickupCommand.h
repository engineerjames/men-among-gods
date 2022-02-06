#ifndef MEN_AMONG_GODS_PICKUP_COMMAND_H
#define MEN_AMONG_GODS_PICKUP_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class PickupCommand : public ClientCommand< CommandType, CommandType::CL_CMD_PICKUP >
{
public:
  PickupCommand( std::uint16_t x, std::uint32_t y );
  virtual ~PickupCommand() = default;

  virtual void send( sf::TcpSocket& socket ) const override;

private:
  std::uint16_t x_;
  std::uint32_t y_;
};
} // namespace MenAmongGods

#endif