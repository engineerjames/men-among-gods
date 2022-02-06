#ifndef MEN_AMONG_GODS_SHOP_COMMAND_H
#define MEN_AMONG_GODS_SHOP_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class ShopCommand : public ClientCommand< CommandType, CommandType::CL_CMD_SHOP >
{
public:
  ShopCommand( std::uint16_t shopNumber, std::uint32_t itemNumber );
  virtual ~ShopCommand() = default;

  virtual void send( sf::TcpSocket& socket ) const override;

private:
  std::uint16_t shopNumber_;
  std::uint32_t itemNumber_;
};
} // namespace MenAmongGods

#endif