#include "SoundCache.h"

#include <SFML/Graphics/Sprite.hpp>

#include "Logger.h"

SoundCache::SoundCache()
    : isLoaded_( false )
    , audioFiles_( N_AUDIO_FILES )
    , sounds_( N_AUDIO_FILES )
    , volume_( 100.0f )
{
}

void SoundCache::loadAudio( const std::string& filePath )
{
  for ( int i = 1; i <= N_AUDIO_FILES; ++i )
  {
    sf::SoundBuffer buffer {};
    if ( ! buffer.loadFromFile( filePath + std::to_string( i ) + ".wav" ) )
    {
      std::cerr << "Unable to load audio file: " << filePath + std::to_string( i ) + ".wav " << std::endl;
    }

    audioFiles_[ i - 1 ] = buffer;

    sf::Sound newSound {};
    newSound.setBuffer( audioFiles_[ i - 1 ] );

    sounds_[ i - 1 ] = newSound;
  }
}

void SoundCache::increaseVolume()
{
  if ( volume_ >= 100.0f )
  {
    return;
  }

  volume_ += 10.0f;

  for ( auto&& s : sounds_ )
  {
    s.setVolume( volume_ );
  }

  std::cerr << "Increased volume." << std::endl;
}

void SoundCache::decreaseVolume()
{
  if ( volume_ <= 0.0f )
  {
    return;
  }

  volume_ -= 10.0f;

  for ( auto&& s : sounds_ )
  {
    s.setVolume( volume_ );
  }

  std::cerr << "Decreased volume." << std::endl;
}

void SoundCache::playSound( std::size_t id )
{

  sounds_[ id - 1 ].play();
}