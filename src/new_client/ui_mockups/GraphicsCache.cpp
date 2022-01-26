#include "GraphicsCache.h"

#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <zip.h>

GraphicsCache::GraphicsCache()
    : sprites_()
{
}

void GraphicsCache::loadSprites( const std::string& filePath )
{
  int              errors {};
  int              fd {};
  struct zip*      za   = nullptr;
  struct zip_file* zf   = nullptr;
  za                    = zip_open( filePath.c_str(), 0, &errors );
  long unsigned int sum = 0;
  int               len = 0;
  char              buf[ 100 ];

  if ( za == nullptr )
  {
    std::cerr << "Unable to open the zip file!" << std::endl;
  }

  std::cerr << "Found " << zip_get_num_entries( za, 0 ) << std::endl;

  struct zip_stat sb;
  for ( unsigned int i = 0; i < zip_get_num_entries( za, 0 ); ++i )
  {
    if ( zip_stat_index( za, i, 0, &sb ) == 0 )
    {
      zf = zip_fopen_index( za, i, 0 );
      if ( ! zf )
      {
        std::cerr << "Error loading file.\n";
        return;
      }

      // bmp/00001.bmp
      fd = open( sb.name, O_RDWR | O_TRUNC | O_CREAT, 0644 );
      if ( fd < 0 )
      {
        std::cerr << "ERROR OPENING FILE!\n";
        return;
      }

      sum = 0;
      while ( sum != sb.size )
      {
        len = zip_fread( zf, buf, 100 );
        if ( len < 0 )
        {
          std::cerr << "Error!\n";
          return;
        }
        write( fd, buf, len );
        sum += len;
      }
      close( fd );
      zip_fclose( zf );
    }
  }

  zip_close( za );
}