#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <array>
#include <memory>

#include "ClientTypes.h"
#include "ConstantIdentifiers.h"

class PlayerData
{
public:
  PlayerData();
  ~PlayerData() = default;

private:
  // Holds the name, description, and some client-related settings (split apart later)
  pdata                         playerInfo_;
  cplayer                       clientSidePlayerInfo_;
  key                           okey_;
  std::unique_ptr< skilltab[] > skillsList_;
  std::unique_ptr< cmap[] >     map_;
};

#endif