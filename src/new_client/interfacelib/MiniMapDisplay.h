#ifndef MEN_AMONG_GODS_MINI_MAP_DISPLAY_H
#define MEN_AMONG_GODS_MINI_MAP_DISPLAY_H

#include <SFML/Graphics.hpp>

#include "ClientTypes.h"
#include "Component.h"

class GraphicsCache;
class GraphicsIndex;
class PlayerData;
class TickBuffer;

namespace MenAmongGods
{
class Map;

class MiniMapDisplay : public MenAmongGods::Component
{
public:
  MiniMapDisplay( MenAmongGods::Map& map, GraphicsCache& cache );
  virtual ~MiniMapDisplay() = default;

  // Component interface
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  // sf::Drawable interface
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  MenAmongGods::Map&                            map_;
  GraphicsCache&                                cache_;
  std::array< sf::RectangleShape, 1024 * 1024 > miniMap_;
  std::array< sf::RectangleShape, 128 * 128 >   miniMapPixelsToDraw_;
};
} // namespace MenAmongGods

#endif