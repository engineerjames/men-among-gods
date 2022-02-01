#ifndef MEN_AMONG_GODS_MAP_DISPLAY_H
#define MEN_AMONG_GODS_MAP_DISPLAY_H

#include <SFML/Graphics.hpp>

#include "../ClientTypes.h"
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
  MapDisplay( MenAmongGods::Map& map, const PlayerData& playerData, const GraphicsCache& cache, const GraphicsIndex& index,
              TickBuffer& tickBuffer, const sf::RenderWindow& window );
  virtual ~MapDisplay() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  void loadFromFile( std::string filePath );
  void saveToFile() const;

private:
  MenAmongGods::Map&        map_;
  const PlayerData&         playerData_;
  const GraphicsCache&      cache_;
  const GraphicsIndex&      index_;
  TickBuffer&               tickBuffer_;
  const sf::RenderWindow&   window_;
  std::vector< sf::Sprite > spritesToDraw_;
  std::size_t               ticker_;
  bool                      needsToUpdate_;
  unsigned int              ctick_;
  int                       tileType_;
  int                       tileX_;
  int                       tileY_;

  void copysprite( int nr, int effect, int xpos, int ypos, int xoff, int yoff );
  int  interpolateItemSprite( int mapIndex );
  int  interpolateCharacterSprite( int mapIndex );
  int  speedo( int n );
  int  speedstep( int n, int d, int s, int update );
};
} // namespace MenAmongGods

#endif