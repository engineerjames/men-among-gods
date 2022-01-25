#ifndef MEN_AMONG_GODS_MAP_H
#define MEN_AMONG_GODS_MAP_H

#include <SFML/Graphics.hpp>

#include "../ClientTypes.h"

namespace MenAmongGods
{
class Map : public sf::Drawable
{
public:
  Map();
  virtual ~Map() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  void loadFromFile( std::string filePath );

private:
  std::unique_ptr< cmap[] > map_;

  void update();
};
} // namespace MenAmongGods

#endif