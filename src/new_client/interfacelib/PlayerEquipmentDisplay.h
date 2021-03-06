#ifndef MEN_AMONG_GODS_PLAYER_EQUIPMENT_DISPLAY
#define MEN_AMONG_GODS_PLAYER_EQUIPMENT_DISPLAY

#include "Component.h"

#include <SFML/Graphics.hpp>

#include <optional>

class PlayerData;
class GraphicsCache;

namespace MenAmongGods
{
class PlayerEquipmentDisplay : public MenAmongGods::Component
{
public:
  static const constexpr unsigned int INVENTORY_SLOTS = 12;

  PlayerEquipmentDisplay( const sf::RenderWindow& window, PlayerData& playerData, GraphicsCache& gfxCache );
  virtual ~PlayerEquipmentDisplay() = default;
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

private:
  const sf::RenderWindow&     window_;
  PlayerData&                 playerData_;
  GraphicsCache&              gfxCache_;
  std::vector< sf::Sprite >   equipmentSprites_;
  std::optional< sf::Sprite > highlightedSprite_;
};
} // namespace MenAmongGods

#endif