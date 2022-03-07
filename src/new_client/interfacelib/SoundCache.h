#ifndef MEN_AMONG_GODS_SOUND_CACHE_H
#define MEN_AMONG_GODS_SOUND_CACHE_H

#include <SFML/Audio.hpp>
#include <string>
#include <vector>

class SoundCache
{
public:
  SoundCache();
  ~SoundCache() = default;

  void loadAudio( const std::string& filePath );
  void playSound( std::size_t id );

  static const constexpr int N_AUDIO_FILES = 18;

  void decreaseVolume();
  void increaseVolume();

private:
  bool                           isLoaded_;
  std::vector< sf::SoundBuffer > audioFiles_;
  std::vector< sf::Sound >       sounds_;
  float                          volume_;
};

#endif