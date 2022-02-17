#ifndef MEN_AMONG_GODS_PLAYER_EQUIPMENT_DISPLAY
#define MEN_AMONG_GODS_PLAYER_EQUIPMENT_DISPLAY

#include "Component.h"

#include <SFML/Graphics.hpp>

class PlayerData;
class GraphicsCache;

namespace MenAmongGods
{
class PlayerEquipmentDisplay : public MenAmongGods::Component
{
public:
  static const constexpr unsigned int INVENTORY_SLOTS = 12;

  PlayerEquipmentDisplay( const PlayerData& playerData, const GraphicsCache& gfxCache );
  virtual ~PlayerEquipmentDisplay() = default;
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