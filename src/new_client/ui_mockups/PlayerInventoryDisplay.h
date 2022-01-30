#ifndef PLAYER_INVENTORY_DISPLAY_H
#define PLAYER_INVENTORY_DISPLAY_H

#include "Component.h"

#include <SFML/Graphics.hpp>

class PlayerData;
class GraphicsCache;

namespace MenAmongGods
{
class PlayerInventoryDisplay : public MenAmongGods::Component
{
public:
  static const constexpr unsigned int INVENTORY_SLOTS = 12;

  PlayerInventoryDisplay( const PlayerData& playerData, const GraphicsCache& gfxCache );
  virtual ~PlayerInventoryDisplay() = default;
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

private:
  const PlayerData&         playerData_;
  const GraphicsCache&      gfxCache_;
  std::vector< sf::Sprite > inventorySprites_;
};
} // namespace MenAmongGods

#endif