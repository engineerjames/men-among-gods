#ifndef GRAPHICS_LOADER_H
#define GRAPHICS_LOADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class GraphicsCache
{
public:
  GraphicsCache();
  ~GraphicsCache() = default;

  static const constexpr unsigned int MAX_SPRITES = 13976;
  static const constexpr unsigned int MAX_ID      = 34191;

  void       loadSprites( const std::string& filePath, const unsigned int howMany );
  sf::Sprite getSprite( std::size_t id ) const;

private:
  bool                       isLoaded_;
  std::vector< sf::Image >   images_;
  std::vector< sf::Texture > textures_;
  std::vector< sf::Sprite >  sprites_;
};

#endif