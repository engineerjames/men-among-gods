#ifndef MEN_AMONG_GODS_MAP_H
#define MEN_AMONG_GODS_MAP_H

#include <SFML/Graphics.hpp>

#include "../ClientTypes.h"

class GraphicsCache;

namespace MenAmongGods
{
class Map : public sf::Drawable
{
public:
  Map( const GraphicsCache& cache );
  virtual ~Map() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  void loadFromFile( std::string filePath );

private:
  std::unique_ptr< cmap[] > map_;
  const GraphicsCache&      cache_;
  std::vector< sf::Sprite > spritesToDraw_;

  void copysprite( int nr, int effect, int xpos, int ypos, int xoff, int yoff );
  void update();
};
} // namespace MenAmongGods

#endif