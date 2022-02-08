#ifndef CLIENT_NETWORK_ACTIVITY_H
#define CLIENT_NETWORK_ACTIVITY_H

#include <atomic>
#include <mutex>
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
  void run() noexcept;
  void stop() noexcept;
  ~ClientNetworkActivity();

  void addClientCommands( const std::vector< std::shared_ptr< MenAmongGods::ClientCommand > >& commandList );

private:
  void startNetworkActivity();

  std::thread                                                   clientNetworkThread_;
  ClientConnection                                              clientConnection_;
  std::atomic< bool >                                           cancellationRequested_;
  bool                                                          isRunning_;
  PlayerData&                                                   playerData_;
  TickBuffer&                                                   tickBuffer_;
  std::vector< std::shared_ptr< MenAmongGods::ClientCommand > > commands_;
  std::mutex                                                    commandMutex_;
};

#endif