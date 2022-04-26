#include "FontCache.h"

#include "GraphicsCache.h"
#include "Logger.h"

namespace MenAmongGods
{
FontCache::FontCache( const std::string& pathToFont )
    : font_()
{
  if ( ! font_.loadFromFile( pathToFont ) )
  {
    LOG_ERROR( "Unable to load font for FontCache!" );
  }
  else
  {
    LOG_DEBUG( "Loaded font: " << font_.getInfo().family );
  }
}

const sf::Font& FontCache::getFont() const
{
  return font_;
}

} // namespace MenAmongGods