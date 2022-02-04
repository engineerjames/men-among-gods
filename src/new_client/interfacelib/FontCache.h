#ifndef FONT_CACHE_H
#define FONT_CACHE_H

#include <SFML/Graphics.hpp>

namespace MenAmongGods
{
class FontCache
{
public:
  // TODO: Add support for multiple fonts
  FontCache( const std::string& pathToFont );

  const sf::Font& getFont() const;

private:
  sf::Font font_;
};
} // namespace MenAmongGods

#endif