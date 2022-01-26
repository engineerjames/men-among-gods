#ifndef GRAPHICS_LOADER_H
#define GRAPHICS_LOADER_H

#include <SFML/Graphics.hpp>
#include <vector>

class GraphicsCache
{
public:
  GraphicsCache();
  ~GraphicsCache() = default;

  void loadSprites(const std::string& filePath);

private:
  std::vector< sf::Sprite > sprites_;
};

#endif