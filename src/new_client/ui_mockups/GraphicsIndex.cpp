#include "GraphicsIndex.h"

#include <fstream>
#include <iostream>

GraphicsIndex::GraphicsIndex( const std::string& pathToIndexFile )
    : indices_()
    , pathToIndexFile_( pathToIndexFile )
    , isLoaded_( false )
{
  indices_.reserve( MAX_INDICES );
}

void GraphicsIndex::load()
{
  std::ifstream gfxidx { pathToIndexFile_, std::ios::binary };

  if ( ! gfxidx.is_open() )
  {
    std::cerr << "Error opening gx00.idx." << std::endl;
    return;
  }

  for ( unsigned int i = 0; i < MAX_INDICES; ++i )
  {
    Index gfxIndex {};

    gfxidx.read( reinterpret_cast< char* >( &gfxIndex ), sizeof( Index ) );

    indices_.push_back( gfxIndex );
  }

  isLoaded_ = true;
}

GraphicsIndex::Index GraphicsIndex::getIndex( std::size_t n ) const
{
  return indices_.at( n );
}
