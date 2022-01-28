#include <fstream>
#include <iostream>
#include <vector>

#include "GraphicsIndex.h"

int main()
{
  GraphicsIndex index { "gfx/gx00.idx" };

  index.load();

  GraphicsIndex::Index idx = index.getIndex( 2000 );

  std::cerr << idx.xs << ", " << idx.ys << std::endl;

  return 0;
}