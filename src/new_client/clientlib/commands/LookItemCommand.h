#ifndef MEN_AMONG_GODS_LOOKITEM_COMMAND_H
#define MEN_AMONG_GODS_LOOKITEM_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class LookItemCommand : public ClientCommand< CommandType, CommandType::CL_CMD_LOOK_ITEM >
{
public:
  LookItemCommand( std::uint16_t x, std::uint32_t y );
  virtual ~LookItemCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::uint16_t x_;
  std::uint32_t y_;
};
} // namespace MenAmongGods

#endif