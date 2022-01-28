#ifndef MEN_AMONG_GODS_MAP_H
#define MEN_AMONG_GODS_MAP_H

#include <SFML/Graphics.hpp>

#include "../ClientTypes.h"
#include "Component.h"

class GraphicsCache;
class GraphicsIndex;

namespace MenAmongGods
{
class Map : public sf::Drawable, public MenAmongGods::Component
{
public:
  Map( const GraphicsCache& cache, const GraphicsIndex& index );
  virtual ~Map() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  void loadFromFile( std::string filePath );

private:
  std::unique_ptr< cmap[] > map_;
  const GraphicsCache&      cache_;
  const GraphicsIndex&      index_;
  std::vector< sf::Sprite > spritesToDraw_;
  std::size_t               ticker_;
  bool                      needsToUpdate_;

  void copysprite( int nr, int effect, int xpos, int ypos, int xoff, int yoff );
  int  interpolateItemSprite( int mapIndex );
  int  interpolateCharacterSprite( int mapIndex );
  int  speedo( int n );
  int  speedstep( int n, int d, int s, int update );
};
} // namespace MenAmongGods

#endif