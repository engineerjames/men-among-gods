#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <array>
#include <memory>
#include <mutex>

#include "ClientTypes.h"
#include "ConstantIdentifiers.h"

class PlayerData
{
public:
  PlayerData();
  ~PlayerData() = default;

  bool        hasPlayerDataChanged() const;
  const char* getPlayerName() const;
  const char* getPlayerDescription() const;

  pdata&    getPlayerInfo();
  cplayer&  getClientSidePlayerInfo();
  cmap*     getMap();
  skilltab* getSkillList();
  key&      getOkey();
  look&     getLook();

  void lock();
  void unlock();

private:
  // Holds the name, description, and some client-related settings (split apart later)
  pdata                         playerInfo_; // This is more what initially gets sent to the server
  bool                          playerDataHasChanged_;
  cplayer                       clientSidePlayerInfo_; // This is more the truth of what your character is...
  key                           okey_;
  std::unique_ptr< skilltab[] > skillsList_;
  std::unique_ptr< cmap[] >     map_;
  look                          look_;
  std::mutex                    ioMutex_;
};

#endif