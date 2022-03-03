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

private:
  sf::Sprite                                            loadSprite( std::size_t id );
  mutable std::vector< sf::Texture >                    textures_;
  mutable std::vector< sf::Sprite >                     sprites_;
  mutable std::unordered_map< std::size_t, sf::Sprite > spriteCache_;
};

#endif