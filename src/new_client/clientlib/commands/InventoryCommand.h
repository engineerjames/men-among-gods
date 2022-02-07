#ifndef MEN_AMONG_GODS_INVENTORY_COMMAND_H
#define MEN_AMONG_GODS_INVENTORY_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class InventoryCommand : public ClientCommand
{
public:
  InventoryCommand( std::uint32_t x, std::uint32_t y, std::uint32_t selectedCharacter );
  virtual ~InventoryCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::uint32_t x_;
  std::uint32_t y_;
  std::uint32_t selectedCharacter_;
};
} // namespace MenAmongGods

#endif