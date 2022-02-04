#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <array>
#include <memory>
#include <mutex>

#include "ClientTypes.h"
#include "ConstantIdentifiers.h"

#include <SFML/Graphics.hpp>

class PlayerData
{
public:
  PlayerData();
  ~PlayerData() = default;

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

  pdata&         getPlayerInfo();
  cplayer&       getClientSidePlayerInfo();
  const cplayer& getClientSidePlayerInfo() const;

  skilltab* getSkillList();
  key&      getOkey();
  look&     getLook();

  void lock();
  void unlock();

  void saveToFile() const;
  void loadFromFile( const std::string& filePath );

  void setName( std::string newName );
  void setPassword( std::string password );
  void setDescription( std::string description );
  void setRaceAndSex( std::string race, std::string sex );

private:
  // Holds the name, description, and some client-related settings (split apart later)
  pdata       playerInfo_; // This is more what initially gets sent to the server
  bool        playerDataHasChanged_;
  cplayer     clientSidePlayerInfo_; // This is more the truth of what your character is...
  key         okey_;
  skilltab*   skillsList_;
  look        look_;
  std::mutex  ioMutex_;
  std::string password_; // TODO: This is super insecure to store it like this long-term
};

#endif