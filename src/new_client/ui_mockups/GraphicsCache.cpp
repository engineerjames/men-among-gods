#include "GraphicsCache.h"

#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iostream>

#ifdef _WIN32

#else
#include <unistd.h>
#include <zip.h>
#endif

#include <SFML/Graphics/Sprite.hpp>

GraphicsCache::GraphicsCache()
    : isLoaded_( false )
    , images_( MAX_ID )
    , textures_( MAX_ID )
    , sprites_( MAX_ID )
{
}

#ifdef _WIN32
void GraphicsCache::loadSprites( const std::string& filePath, const unsigned int howMany )
{
  std::cerr << "LOADING SPRITES NOT SUPPORTED YET!" << filePath << ", " << howMany << std::endl;
}
#else

void GraphicsCache::loadSprites( const std::string& filePath, const unsigned int howMany )
{
  struct zip*      za = nullptr;
  struct zip_file* zf = nullptr;
  char             buf[ 2 * 1024 * 1024 ]; // 2MB

  int errors {};
  za = zip_open( filePath.c_str(), 0, &errors );

  if ( za == nullptr )
  {
    std::cerr << "Unable to open the zip file!" << std::endl;
  }

  std::cerr << "Loading " << howMany << " of " << zip_get_num_entries( za, 0 ) << std::endl;

  struct zip_stat sb;

  unsigned int offSet = 0;
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

      // bmp/00001.bmp - example of sb.name
      // But we want the index in the vector to align with the filename itself.
      // For example... we want 00001.bmp to be sprites_[1];
      //                        00047.bmp to be sprites_[47];
      std::filesystem::path gfxFile { sb.name };
      if ( gfxFile.has_filename() )
      {
        auto gfxName = gfxFile.filename();
        int  index   = std::stoi( gfxName.string() );
        offSet       = index - i;
      }

      // Ensure the filename matches with the index.
      // This will force some 'holes' in our data structure
      sf::Image&   newImage   = images_[ i + offSet ];
      sf::Texture& newTexture = textures_[ i + offSet ];
      sf::Sprite&  newSprite  = sprites_[ i + offSet ];

      if ( static_cast< unsigned long >( zip_fread( zf, buf, sb.size ) ) != sb.size )
      {
        std::cerr << "Unable to read entire zip file." << std::endl;
      }

      if ( ! newImage.loadFromMemory( buf, sb.size ) )
      {
        std::cerr << "Error loading image from memory." << std::endl;
      }
      else
      {
        // Great, some images have masks of 254 0 254 as well
        newImage.createMaskFromColor( sf::Color { 0xFF00FFFF } );
        newImage.createMaskFromColor( sf::Color { 0xFE00FEFF } );

        // Load in textures and sprites for now, though this is probably unnecessary work
        newTexture.loadFromImage( newImage );

        newSprite.setTexture( newTexture );

        if ( ( i + offSet ) > images_.capacity() )
        {
          std::cerr << "Underallocated buffers - need at least a capacity of " << ( i + offSet ) << std::endl;
          return;
        }

        if ( i == howMany )
        {
          break;
        }
      }

      zip_fclose( zf );
    }
  }

  zip_close( za );

  isLoaded_ = true;
}
#endif

sf::Sprite GraphicsCache::getSprite( std::size_t id ) const
{
  return sprites_.at( id );
}