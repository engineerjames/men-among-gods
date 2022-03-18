#ifndef GRAPHICS_LOADER_H
#define GRAPHICS_LOADER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

class GraphicsCache
{
public:
  GraphicsCache();
  ~GraphicsCache() = default;

  static const constexpr unsigned int MAX_SPRITES = 13976;
  static const constexpr unsigned int MAX_ID      = 34191;

  void loadNewGfxCache();

  void correctPosition( int index, sf::Vector2f& position );

  sf::Sprite getSprite( std::size_t id );
  sf::Color  getAvgColor( std::size_t id );

  struct NewGfxCacheEntry
  {
    std::size_t  id;
    std::string  file;
    sf::Vector2f old_dimensions;
    sf::Vector2f new_dimensions;
    sf::Vector2f scaling_factor;
  };

  struct SpriteCacheEntry
  {
    sf::Sprite sprite;
    sf::Color  avgColor;
  };

private:
  void                                                loadSprite( std::size_t id );
  std::vector< sf::Texture >                          textures_;
  std::vector< sf::Sprite >                           sprites_;
  std::unordered_map< std::size_t, SpriteCacheEntry > spriteCache_;
  std::unordered_map< std::size_t, NewGfxCacheEntry > newGfxCache_;
};

#endif