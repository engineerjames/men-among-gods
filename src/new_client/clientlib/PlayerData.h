#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <array>
#include <memory>
#include <mutex>
#include <tuple>

#include "ClientTypes.h"
#include "ConstantIdentifiers.h"

#include <SFML/Graphics.hpp>

class PlayerData
{
public:
  PlayerData();
  ~PlayerData() = default;

  struct LogMessage
  {
    LogType     type;
    std::string msg;

    LogMessage( LogType theType, const std::string& theMsg )
        : type( theType )
        , msg( theMsg )
    {
    }
  };

  typedef std::tuple< long unsigned int, long unsigned int > OkeyPasswordType;

  bool         hasPlayerDataChanged() const;
  const char*  getPlayerName() const;
  const char*  getPlayerDescription() const;
  std::uint8_t areWallsHidden() const;
  int          getPlayerDirection() const;
  sf::Vector2i getGotoPosition() const;
  int          getPlayerAction() const;
  int          getFirstTarget() const;
  int          getSecondTarget() const;
  int          clientShouldShowNames() const;
  int          clientShouldShowPercentHealth() const;
  int          getAttackTarget() const;

  // TODO: Eliminate this series of "get" calls--need just a plethora of get/set commands
  // for the underlying data values so they can be properly protected from multi-threaded
  // collisions.
  cplayer&       getClientSidePlayerInfo();
  const cplayer& getClientSidePlayerInfo() const;
  look&          getLook();
  void           sortSkills();

  void lock();
  void unlock();

  void saveToFile() const;
  void loadFromFile( const std::string& filePath );

  void setName( std::string newName );
  void setPassword( std::string password );
  void setPassword( long unsigned int pass1, long unsigned int pass2 );
  void setDescription( std::string description );
  void setRaceAndSex( std::string race, std::string sex );
  void setRaceAndSex( long unsigned int race );
  void setUserNumber( long unsigned int usnr );
  void setClientShouldShowNames( bool shouldShowNames );
  void setClientShouldShowPercentHealth( bool shouldShowPercentHealth );
  void setClientShouldHideWalls( bool shouldHideWalls );
  void setOkeyName( char ( &pdataName )[ 40 ] );

  long unsigned int getRaceAndSex() const;
  std::string       getPassword() const;
  OkeyPasswordType  getPasswordOkeyValues() const;
  long unsigned int getUserNumber() const;

  void                             addLogMessage( LogType type, const std::string& msg );
  const std::vector< LogMessage >& getLogMessages() const;

private:
  // Holds the name, description, and some client-related settings (split apart later)
  pdata                     playerInfo_; // This is more what initially gets sent to the server
  bool                      playerDataHasChanged_;
  cplayer                   clientSidePlayerInfo_; // This is more the truth of what your character is...
  key                       okey_;
  skilltab*                 skillsList_;
  look                      look_;
  std::mutex                ioMutex_;
  std::string               password_; // TODO: This is super insecure to store it like this long-term
  std::vector< LogMessage > messages_;
};

#endif