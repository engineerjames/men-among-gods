#ifndef MEN_AMONG_GODS_MAP_DISPLAY_H
#define MEN_AMONG_GODS_MAP_DISPLAY_H

#include <SFML/Graphics.hpp>

#include "ClientTypes.h"
#include "Component.h"

#include <set>

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

  struct MapSprite
  {
    enum struct SpriteType
    {
      Tile,
      Character,
      Object,
      Unspecified
    };

    sf::Sprite       sprite;
    int              index;
    SpriteType       type;
    sf::RenderStates renderState;

    MapSprite( sf::Sprite sprite_, int index_, SpriteType type_ )
        : sprite( sprite_ )
        , index( index_ )
        , type( type_ )
        , renderState( sf::BlendAlpha )
    {
    }
  };

private:
  void         copysprite( int index, int nr, int effect, int xpos, int ypos, int xoff, int yoff, unsigned char light,
                           MapSprite::SpriteType spriteType, bool isCharacterSelected = false );
  void         copyEffectSprite( int index, int nr, int xpos, int ypos, int xoff, int yoff, sf::Color effectColor );
  sf::Vector2i dd_gputtext( int xpos, int ypos, std::string text, int xoff, int yoff );

  typedef std::vector< MapDisplay::MapSprite >::iterator MapSpriteIterator;

  MapSpriteIterator getSpriteByType( const std::set< int >& mapIndicesToCheck, MapSprite::SpriteType spriteType );

  const sf::Font&                   font_;
  MenAmongGods::Map&                map_;
  PlayerData&                       playerData_;
  GraphicsCache&                    cache_;
  const GraphicsIndex&              index_;
  const sf::RenderWindow&           window_;
  std::vector< MapSprite >          spritesToDraw_;
  std::vector< sf::Text >           textToDraw_;
  std::vector< sf::RectangleShape > healthBarsToDraw_;
  int                               tileType_;
  int                               tileX_;
  int                               tileY_;
  int                               lastHoveredIndex_;
};
} // namespace MenAmongGods

#endif