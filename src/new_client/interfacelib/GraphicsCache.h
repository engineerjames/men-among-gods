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

  sf::Sprite getSprite( std::size_t id );
  sf::Color  getAvgColor( std::size_t id );

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
};

#endif