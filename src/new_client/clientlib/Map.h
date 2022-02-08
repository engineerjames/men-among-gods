#ifndef MEN_AMONG_GODS_MAP_H
#define MEN_AMONG_GODS_MAP_H

#include <memory>
#include <mutex>

#include "ClientTypes.h"
#include "ConstantIdentifiers.h"

namespace MenAmongGods
{
class Map
{
public:
  Map();
  ~Map() = default;

  // We'll start by naively allowing access to the entirety of the map through
  // public "lock" and "unlock" functions.
  void        unlock();
  void        lock();
  cmap*       getMap();
  const cmap* getMap() const;
  void        setCTick( int newValue );
  void        setTicker( std::size_t newValue );

  void tick();

private:
  int speedstep( int n, int d, int s, int update );
  int interpolateItemSprite( unsigned int mapIndex );
  int interpolateCharacterSprite( unsigned int mapIndex );
  int speedo( unsigned int n );

  std::array< cmap, MAPX * MAPY > map_;
  std::mutex                      mapMutex_;
  int                             ctick_;
  std::size_t                     ticker_;
};
} // namespace MenAmongGods

#endif