#ifndef CLIENT_NETWORK_ACTIVITY_H
#define CLIENT_NETWORK_ACTIVITY_H

#include <atomic>
#include <string>
#include <thread>

#include "ClientConnection.h"
#include "Compressor.h"

class ClientNetworkActivity
{
public:
  ClientNetworkActivity( pdata& playerData, const std::string &hostIp, unsigned short hostPort );
  void run( ) noexcept;
  void stop() noexcept;
  ~ClientNetworkActivity();

private:
  void startNetworkActivity( );

  std::thread         clientNetworkThread_;
  Compressor          compressor_;
  ClientConnection    clientConnection_;
  std::atomic< bool > cancellationRequested_;
  bool                isRunning_;
  pdata &             playerData_;
};

#endif