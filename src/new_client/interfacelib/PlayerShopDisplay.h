#ifndef MEN_AMONG_GODS_PLAYER_SHOP_DISPLAY_H
#define MEN_AMONG_GODS_PLAYER_SHOP_DISPLAY_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Component.h"

class PlayerData;
class GraphicsCache;
class GraphicsIndex;

namespace MenAmongGods
{
class PlayerShopDisplay : public MenAmongGods::Component
{
public:
  PlayerShopDisplay( const sf::RenderWindow& window, const PlayerData& pdata, const GraphicsCache& gfxCache,
                     const GraphicsIndex& gfxIndex );
  virtual ~PlayerShopDisplay() = default;

  // Component interface
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  // sf::Drawable interface
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  const sf::RenderWindow& window_;
  const PlayerData&       playerData_;
  const GraphicsCache&    gfxCache_;
  const GraphicsIndex&    gfxIndex_;

  sf::Sprite                shopBackground_;
  std::vector< sf::Sprite > itemSprites_;
};
} // namespace MenAmongGods

#endif