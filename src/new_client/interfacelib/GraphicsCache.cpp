#include "GraphicsCache.h"

#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <zip.h>

#include <SFML/Graphics/Sprite.hpp>

#include "ResourceLocations.h"

#include "Logger.h"

GraphicsCache::GraphicsCache()
    : textures_( MAX_ID + 1 )
    , sprites_( MAX_ID + 1 )
    , spriteCache_()
{
}

sf::Sprite GraphicsCache::loadSprite( std::size_t id )
{
  static std::vector< sf::Image > images { MAX_ID + 1 };

  // All BMP and PNG images have 5 places
  // 1     --> 00001.bmp
  // 23532 --> 23532.bmp
  std::string idString      = std::to_string( id );
  std::size_t numberOfZeros = 5 - idString.length();

  std::stringstream filenameStream {};

  for ( std::size_t i = 0; i < numberOfZeros; ++i )
  {
    filenameStream << '0';
  }

  filenameStream << idString;

  std::string fileName = filenameStream.str();

  std::string sourceDirectory = MenAmongGods::getGfxRoot();
  for ( const auto& f : std::filesystem::recursive_directory_iterator( sourceDirectory ) )
  {
    if ( f.is_regular_file() && f.path().has_filename() && ( f.path().filename().replace_extension() == fileName ) )
    {
      std::string fileToLoad = f.path().string();

      sf::Image&   newImage   = images[ id ];
      sf::Texture& newTexture = textures_[ id ];
      sf::Sprite&  newSprite  = sprites_[ id ];

      if ( ! newImage.loadFromFile( fileToLoad ) )
      {
        LOG_ERROR( "Error loading image from memory" );
      }
      else
      {
        // The BMP graphics files are NOT consistent in their usage of masks for transparency...
        static std::array< sf::Color, 9 > masks = { sf::Color { 0xFF00FFFF }, sf::Color { 0xFE00FEFF }, sf::Color { 0xFD00FDFF },
                                                    sf::Color { 0xFC00FCFF }, sf::Color { 0xFB00FBFF }, sf::Color { 0xFA00FAFF },
                                                    sf::Color { 0xF900F9FF }, sf::Color { 0xF800F8FF }, sf::Color { 0xF700F7FF } };

        for (auto&& mask : masks)
        {
          newImage.createMaskFromColor( mask );
        }

        // Load in textures and sprites for now, though this is probably unnecessary work
        newTexture.loadFromImage( newImage );

        newSprite.setTexture( newTexture );

        return newSprite;
      }
    }
  }

  // Worst-case just return a default-constructed sprite which will render white on the screen
  // which will look obviously wrong...
  return sf::Sprite {};
}

sf::Sprite GraphicsCache::getSprite( std::size_t id )
{
  if ( spriteCache_.count( id ) == 0 )
  {
    spriteCache_[ id ] = loadSprite( id );
  }

  return spriteCache_[ id ];
}