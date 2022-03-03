#ifndef MEN_AMONG_GODS_MAP_DISPLAY_H
#define MEN_AMONG_GODS_MAP_DISPLAY_H

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

class MapDisplay : public MenAmongGods::Component
{
public:
  MapDisplay( const sf::Font& font, MenAmongGods::Map& map, PlayerData& playerData, GraphicsCache& cache, const GraphicsIndex& index,
              const sf::RenderWindow& window );
  virtual ~MapDisplay() = default;

  // Component interface
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  // sf::Drawable interface
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  void loadFromFile( std::string filePath );
  void saveToFile() const;

private:
  void         copysprite( int nr, int effect, int xpos, int ypos, int xoff, int yoff, bool isCharacterSelected = false );
  sf::Vector2i dd_gputtext( int xpos, int ypos, std::string text, int xoff, int yoff );

  const sf::Font&           font_;
  MenAmongGods::Map&        map_;
  PlayerData&               playerData_;
  GraphicsCache&            cache_;
  const GraphicsIndex&      index_;
  const sf::RenderWindow&   window_;
  std::vector< sf::Sprite > spritesToDraw_;
  std::vector< sf::Text >   textToDraw_;
  int                       tileType_;
  int                       tileX_;
  int                       tileY_;
};
} // namespace MenAmongGods

#endif