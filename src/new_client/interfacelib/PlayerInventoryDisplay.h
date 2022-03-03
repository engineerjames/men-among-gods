#ifndef MEN_AMONG_GODS_PLAYER_INVENTORY_DISPLAY
#define MEN_AMONG_GODS_PLAYER_INVENTORY_DISPLAY

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

  PlayerInventoryDisplay( const sf::RenderWindow& window, const PlayerData& playerData, GraphicsCache& gfxCache );
  virtual ~PlayerInventoryDisplay() = default;
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

private:
  const sf::RenderWindow&   window_;
  const PlayerData&         playerData_;
  GraphicsCache&            gfxCache_;
  std::vector< sf::Sprite > equipmentSprites_;

  sf::RectangleShape scrollBar_;
  sf::FloatRect      upArrow_;
  sf::FloatRect      downArrow_;
  int                scrollPosition_;
};
} // namespace MenAmongGods

#endif