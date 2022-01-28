#include "Map.h"

#include "ConstantIdentifiers.h"

namespace MenAmongGods
{
Map::Map()
    : map_( std::make_unique< cmap[] >( MAPX * MAPY ) )
    , mapMutex_()
{
  for ( unsigned int i = 0; i < MAPX * MAPY; ++i )
  {
    map_[ i ].ba_sprite = SPR_EMPTY;
  }
}

void Map::lock()
{
  mapMutex_.lock();
}

cmap* Map::getMap()
{
  return map_.get();
}

void Map::unlock()
{
  mapMutex_.unlock();
}

} // namespace MenAmongGods