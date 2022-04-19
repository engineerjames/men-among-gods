#ifndef CLIENT_NETWORK_ACTIVITY_H
#define CLIENT_NETWORK_ACTIVITY_H

#include <string>
#include <thread>

#include "ClientConnection.h"
#include "Compressor.h"

class TickBuffer;

namespace MenAmongGods
{
class Map;
class ClientCommand;
} // namespace MenAmongGods

class PlayerData;

class ClientNetworkActivity
{
public:
  ClientNetworkActivity( TickBuffer& tickBuffer, PlayerData& playerData, const std::string& hostIp, unsigned short hostPort );

  void addClientCommands( const std::vector< std::shared_ptr< MenAmongGods::ClientCommand > >& commandList );

  void login() noexcept;
  void processServerTicks() noexcept;
  void sendCommands() noexcept;

private:
  ClientConnection                                              clientConnection_;
  PlayerData&                                                   playerData_;
  TickBuffer&                                                   tickBuffer_;
  std::vector< std::shared_ptr< MenAmongGods::ClientCommand > > commands_;
  sf::Time                                                      timeSinceLastTickSent_;
  sf::Clock                                                     clock_;
};

#endif