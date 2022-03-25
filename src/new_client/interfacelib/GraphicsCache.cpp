#include "GraphicsCache.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <SFML/Graphics/Sprite.hpp>
#include <json/json.h>

#include "ResourceLocations.h"

#include "Logger.h"

GraphicsCache::GraphicsCache()
    : textures_( MAX_ID + 1 )
    , sprites_( MAX_ID + 1 )
    , spriteCache_()
{
}

void GraphicsCache::loadNewGfxCache()
{
  // Let's read in the configuration JSON file first
  std::string newGfxConfigPath = MenAmongGods::getConfigPath() + "gfxConfig.json";

  std::ifstream newGfxFile { newGfxConfigPath };

  Json::Value root {};

  newGfxFile >> root;

  for ( const auto& entry : root[ "gfx" ] )
  {
    NewGfxCacheEntry cacheEntry {};

    cacheEntry.id   = entry[ "id" ].asInt();
    cacheEntry.file = entry[ "file" ].asString();

    float newX = entry[ "new_dimensions" ][ "width" ].asFloat();
    float newY = entry[ "new_dimensions" ][ "height" ].asFloat();

    float oldX = entry[ "old_dimensions" ][ "width" ].asFloat();
    float oldY = entry[ "old_dimensions" ][ "height" ].asFloat();

    float offsetX = entry[ "offset" ][ "width" ].asFloat();
    float offsetY = entry[ "offset" ][ "height" ].asFloat();

    cacheEntry.offset = sf::Vector2f { offsetX, offsetY };

    cacheEntry.new_dimensions = sf::Vector2f { newX, newY };
    cacheEntry.old_dimensions = sf::Vector2f { oldX, oldY };

    cacheEntry.scaling_factor.x = cacheEntry.old_dimensions.x / cacheEntry.new_dimensions.x;
    cacheEntry.scaling_factor.y = cacheEntry.old_dimensions.y / cacheEntry.new_dimensions.y;

    newGfxCache_[ cacheEntry.id ] = cacheEntry;
  }
}

sf::Color GraphicsCache::getAvgColor( std::size_t id )
{
  // Load the sprite if not already in the cache
  if ( spriteCache_.count( id ) == 0 )
  {
    loadSprite( id );
  }

  return spriteCache_[ id ].avgColor;
}

void GraphicsCache::correctPosition( int index, sf::Vector2f& position )
{
  if ( newGfxCache_.count( index ) == 0 )
  {
    return;
  }

  position.x += newGfxCache_[ index ].offset.x;
  position.y += newGfxCache_[ index ].offset.y;
}

void GraphicsCache::loadSprite( std::size_t id )
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

      bool hasNewGfxEntry = false;
      if ( newGfxCache_.count( id ) != 0 )
      {
        fileToLoad     = MenAmongGods::getNewGfxRoot() + newGfxCache_[ id ].file;
        hasNewGfxEntry = true;
      }

      if ( ! newImage.loadFromFile( fileToLoad ) )
      {
        LOG_ERROR( "Error loading image from memory" );
      }
      else
      {

        // We only need to apply masks to the images that use the 'pink' color for transparency
        if ( ! hasNewGfxEntry )
        {
          // The BMP graphics files are NOT consistent in their usage of masks for transparency...
          static std::array< sf::Color, 9 > masks = { sf::Color { 0xFF00FFFF }, sf::Color { 0xFE00FEFF }, sf::Color { 0xFD00FDFF },
                                                      sf::Color { 0xFC00FCFF }, sf::Color { 0xFB00FBFF }, sf::Color { 0xFA00FAFF },
                                                      sf::Color { 0xF900F9FF }, sf::Color { 0xF800F8FF }, sf::Color { 0xF700F7FF } };

          for ( auto&& mask : masks )
          {
            newImage.createMaskFromColor( mask );
          }
        }

        // Load in textures and sprites for now, though this is probably unnecessary work
        newTexture.loadFromImage( newImage );
        newSprite.setTexture( newTexture );

        unsigned int averagePixelColor_Red {};
        unsigned int averagePixelColor_Green {};
        unsigned int averagePixelColor_Blue {};

        int newImageSize = 0;
        for ( unsigned int i = 0; i < newImage.getSize().x; ++i )
        {
          for ( unsigned int j = 0; j < newImage.getSize().y; ++j )
          {
            if ( newImage.getPixel( i, j ).a == 0 )
            {
              continue;
            }

            newImageSize++;

            averagePixelColor_Red += newImage.getPixel( i, j ).r;
            averagePixelColor_Green += newImage.getPixel( i, j ).g;
            averagePixelColor_Blue += newImage.getPixel( i, j ).b;
          }
        }

        if ( newImageSize != 0 )
        {
          averagePixelColor_Red /= newImageSize;
          averagePixelColor_Green /= newImageSize;
          averagePixelColor_Blue /= newImageSize;
        }

        if ( hasNewGfxEntry )
        {
          newSprite.setScale( newGfxCache_[ id ].scaling_factor.x, newGfxCache_[ id ].scaling_factor.y );
        }

        spriteCache_[ id ].sprite = newSprite;
        spriteCache_[ id ].avgColor =
            sf::Color { static_cast< std::uint8_t >( averagePixelColor_Red ), static_cast< std::uint8_t >( averagePixelColor_Green ),
                        static_cast< std::uint8_t >( averagePixelColor_Blue ), static_cast< std::uint8_t >( 255u ) };
        return;
      }
    }
  }

  // Worst-case just return a default-constructed sprite which will render white on the screen
  // which will look obviously wrong...
  std::cerr << "ERROR loading sprite: " << id << std::endl;
}

sf::Sprite GraphicsCache::getSprite( std::size_t id )
{
  if ( spriteCache_.count( id ) == 0 )
  {
    loadSprite( id );
  }

  return spriteCache_[ id ].sprite;
}