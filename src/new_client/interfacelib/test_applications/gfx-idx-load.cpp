#include <fstream>
#include <iostream>
#include <vector>

#include "GraphicsIndex.h"
#include "ResourceLocations.h"

int main()
{
  GraphicsIndex index { MenAmongGods::getGfxRoot() + "gx00.idx" };

  index.load();

  GraphicsIndex::Index idx = index.getIndex( 2000 );

  std::cerr << idx.xs << ", " << idx.ys << std::endl;

  return 0;
}