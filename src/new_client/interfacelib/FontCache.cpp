#include "FontCache.h"

#include <iostream>

namespace MenAmongGods
{
FontCache::FontCache( const std::string& pathToFont )
    : font_()
{
  if ( ! font_.loadFromFile( pathToFont ) )
  {
    std::cerr << "Unable to load font for FontCache!" << std::endl;
  }
  else
  {
    std::cerr << "Loaded font: " << font_.getInfo().family << std::endl;
  }
}

const sf::Font& FontCache::getFont() const
{
  return font_;
}

} // namespace MenAmongGods