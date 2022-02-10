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
  MapDisplay( const sf::Font& font, MenAmongGods::Map& map, const PlayerData& playerData, const GraphicsCache& cache,
              const GraphicsIndex& index, const sf::RenderWindow& window );
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
  int          getMapIndexFromMousePosition( const sf::Vector2f& mousePosition, bool setTileOutline );
  std::string  lookup( int nr, unsigned short id );
  void         set_look_proz( unsigned short nr, unsigned short id, int proz );
  void         copysprite( int nr, int effect, int xpos, int ypos, int xoff, int yoff );
  sf::Vector2i dd_gputtext( int xpos, int ypos, std::string text, int xoff, int yoff );

  const sf::Font&                   font_;
  MenAmongGods::Map&                map_;
  const PlayerData&                 playerData_;
  const GraphicsCache&              cache_;
  const GraphicsIndex&              index_;
  const sf::RenderWindow&           window_;
  std::vector< sf::Sprite >         spritesToDraw_;
  std::vector< sf::Text >           textToDraw_;
  int                               tileType_;
  int                               tileX_;
  int                               tileY_;
  std::map< unsigned short, looks > lookMap;
  int                               lookat;
};
} // namespace MenAmongGods

#endif