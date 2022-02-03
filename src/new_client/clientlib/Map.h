#ifndef MEN_AMONG_GODS_MAP_H
#define MEN_AMONG_GODS_MAP_H

#include <memory>
#include <mutex>

#include "ClientTypes.h"

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

private:
  std::unique_ptr< cmap[] > map_;
  std::mutex                mapMutex_;
};
} // namespace MenAmongGods

#endif