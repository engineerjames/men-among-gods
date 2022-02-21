#include "GraphicsCache.h"

#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <zip.h>

#include <SFML/Graphics/Sprite.hpp>

#include "Logger.h"

GraphicsCache::GraphicsCache()
    : isLoaded_( false )
    , images_( MAX_ID + 1 )
    , textures_( MAX_ID + 1 )
    , sprites_( MAX_ID + 1 )
{
}

// TODO: Fix this up later
#ifdef WIN32
void GraphicsCache::loadSprites( const std::string& filePath, const unsigned int howMany )
{
  struct zip*      za  = nullptr;
  struct zip_file* zf  = nullptr;
  std::byte*       buf = new std::byte[ 2 * 1024 * 1024 ](); // 2MB

  int errors {};
  za = zip_open( filePath.c_str(), 0, &errors );

  if ( za == nullptr )
  {
    LOG_ERROR( "Unable to open the zip file!" );
  }

  LOG_DEBUG( "Loading " << zip_get_num_entries( za, 0 ) << " files from the ZIP." );

  struct zip_stat sb = {};

  unsigned int offSet = 0;
  for ( unsigned int i = 0; i < zip_get_num_entries( za, 0 ); ++i )
  {
    if ( zip_stat_index( za, i, 0, &sb ) == 0 )
    {
      zf = zip_fopen_index( za, i, 0 );
      if ( ! zf )
      {
        LOG_ERROR( "Error loading file." );
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
        LOG_ERROR( "Unable to read the entire zip file." );
      }
      else
      {
        // Write file to disk
        std::ofstream outFile { gfxFile.filename(), std::ios::binary };
        outFile.write( reinterpret_cast< const char* >( buf ), sb.size );
      }

      if ( ! newImage.loadFromFile( gfxFile.filename().string() ) )
      {
        LOG_ERROR( "Error loading image from memory" );
      }
      else
      {
        // Great, some images have masks of 254 0 254 as well
        newImage.createMaskFromColor( sf::Color { 0xFF00FFFF } );
        newImage.createMaskFromColor( sf::Color { 0xFE00FEFF } );

        // Yeah, there's just a FEW that have 251 0 251 as well...
        newImage.createMaskFromColor( sf::Color { 0xFB00FBFF } );

        // Load in textures and sprites for now, though this is probably unnecessary work
        newTexture.loadFromImage( newImage );

        newSprite.setTexture( newTexture );

        if ( ( i + offSet ) > images_.capacity() )
        {
          LOG_ERROR( "Underallocated buffers - need at least a capacity of " << ( i + offSet ) );
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
#else
void GraphicsCache::loadSprites( const std::string& filePath, const unsigned int howMany )
{
  struct zip*      za  = nullptr;
  struct zip_file* zf  = nullptr;
  std::byte*       buf = new std::byte[ 2 * 1024 * 1024 ](); // 2MB

  int errors {};
  za = zip_open( filePath.c_str(), 0, &errors );

  if ( za == nullptr )
  {
    LOG_ERROR( "Unable to open the zip file!" );
  }

  LOG_DEBUG( "Loading " << zip_get_num_entries( za, 0 ) << " files from the ZIP." );

  struct zip_stat sb = {};

  unsigned int offSet = 0;
  for ( unsigned int i = 0; i < zip_get_num_entries( za, 0 ); ++i )
  {
    if ( zip_stat_index( za, i, 0, &sb ) == 0 )
    {
      zf = zip_fopen_index( za, i, 0 );
      if ( ! zf )
      {
        LOG_ERROR( "Error loading file." );
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
        LOG_ERROR( "Unable to read the entire zip file." );
      }

      if ( ! newImage.loadFromMemory( reinterpret_cast< void* >( buf ), sb.size ) )
      {
        LOG_ERROR( "Error loading image from memory" );
      }
      else
      {
        // Great, some images have masks of 254 0 254 as well
        newImage.createMaskFromColor( sf::Color { 0xFF00FFFF } );
        newImage.createMaskFromColor( sf::Color { 0xFE00FEFF } );

        // Yeah, there's just a FEW that have 251 0 251 as well...
        newImage.createMaskFromColor( sf::Color { 0xFB00FBFF } );

        // Load in textures and sprites for now, though this is probably unnecessary work
        newTexture.loadFromImage( newImage );

        newSprite.setTexture( newTexture );

        if ( ( i + offSet ) > images_.capacity() )
        {
          LOG_ERROR( "Underallocated buffers - need at least a capacity of " << ( i + offSet ) );
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