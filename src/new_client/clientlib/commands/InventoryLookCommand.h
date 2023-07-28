#ifndef MEN_AMONG_GODS_INVENTORY_LOOK_COMMAND_H
#define MEN_AMONG_GODS_INVENTORY_LOOK_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class InventoryLookCommand : public ClientCommand
{
public:
  InventoryLookCommand( std::uint32_t x, std::uint32_t selectedCharacter );
  virtual ~InventoryLookCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;
  virtual nlohmann::json toJson() const override;

private:
  std::uint32_t x_;
  std::uint32_t selectedCharacter_;
};
} // namespace MenAmongGods

#endif