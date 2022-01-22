#ifndef CLIENT_NETWORK_ACTIVITY_H
#define CLIENT_NETWORK_ACTIVITY_H

#include <atomic>
#include <string>
#include <thread>

#include "ClientConnection.h"
#include "Compressor.h"
#include "PlayerData.h"

class ClientNetworkActivity
{
public:
  ClientNetworkActivity( PlayerData& playerData, const std::string& hostIp, unsigned short hostPort );
  void run() noexcept;
  void stop() noexcept;
  ~ClientNetworkActivity();

private:
  void startNetworkActivity();

  std::thread         clientNetworkThread_;
  ClientConnection    clientConnection_;
  std::atomic< bool > cancellationRequested_;
  bool                isRunning_;
  PlayerData&         playerData_;
};

#endif