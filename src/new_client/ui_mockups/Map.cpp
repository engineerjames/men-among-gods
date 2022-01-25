#include "Map.h"

#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>

#include "../ConstantIdentifiers.h"

namespace MenAmongGods
{

Map::Map()
    : map_( std::make_unique< cmap[] >( MAPX * MAPY ) )
{
}

void Map::draw( sf::RenderTarget&, sf::RenderStates ) const
{
  // target.draw()
}

void Map::loadFromFile( std::string filePath )
{
  std::ifstream                 mapFile( filePath );
  boost::archive::text_iarchive ia( mapFile );

  cmap tmpMap {};
  if ( mapFile.is_open() )
  {
    for ( unsigned int x = 0; x < MAPX; ++x )
    {
      for ( unsigned int y = 0; y < MAPY; ++y )
      {
        ia >> tmpMap;
        map_[ x + y * MAPX ] = tmpMap;
      }
    }
  }

  mapFile.close();
}

} // namespace MenAmongGods