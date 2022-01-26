#include "GraphicsCache.h"

#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <zip.h>

GraphicsCache::GraphicsCache()
    : images_()
    , textures_()
    , sprites_()
{
  images_.reserve( 15000 );
  textures_.reserve( 15000 );
  sprites_.reserve( 15000 );
}

void GraphicsCache::loadSprites( const std::string& filePath )
{
  int              errors {};
  struct zip*      za = nullptr;
  struct zip_file* zf = nullptr;
  za                  = zip_open( filePath.c_str(), 0, &errors );
  char buf[ 2 * 1024 * 1024 ]; // 2MB

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

      // bmp/00001.bmp - example of sb.name
      sf::Image   newImage {};
      sf::Texture texture {};
      sf::Sprite  sprite {};

      if ( static_cast< unsigned long >( zip_fread( zf, buf, sb.size ) ) != sb.size )
      {
        std::cerr << "Unable to read entire zip file." << std::endl;
      }

      if ( ! newImage.loadFromMemory( buf, sb.size ) )
      {
        std::cerr << "Error loading image from memory" << std::endl;
      }
      else
      {
        // Great, some images have masks of 254 0 254 as well
        newImage.createMaskFromColor( sf::Color { 0xFF00FFFF } );
        newImage.createMaskFromColor( sf::Color { 0xFE00FEFF } );

        // Load in textures and sprites for now, though this is probably unnecessary work
        texture.loadFromImage( newImage );

        sprite.setTexture( texture );

        images_[ i ]   = std::move( newImage );
        textures_[ i ] = std::move( texture );
        sprites_[ i ]  = std::move( sprite );
      }

      zip_fclose( zf );
    }
  }

  zip_close( za );
}