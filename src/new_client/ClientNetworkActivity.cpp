#include "ClientNetworkActivity.h"

#include <cstring>
#include <iostream>

#include "ConstantIdentifiers.h"
#include "TickBuffer.h"

ClientNetworkActivity::~ClientNetworkActivity()
{
  // Attempt to force the child thread to stop processing
  // and join().
  if ( cancellationRequested_.load() == false )
  {
    cancellationRequested_.store( true );
  }

  if ( clientNetworkThread_.joinable() )
  {
    clientNetworkThread_.join();
  }
}

ClientNetworkActivity::ClientNetworkActivity( PlayerData& playerData, const std::string& hostIp, unsigned short hostPort )
    : clientNetworkThread_()
    , clientConnection_( hostIp, hostPort )
    , cancellationRequested_( false )
    , isRunning_( false )
    , playerData_( playerData )
{
}

void ClientNetworkActivity::run() noexcept
{
  if ( isRunning_ )
  {
    return;
  }

  isRunning_ = true;

  clientNetworkThread_ = std::thread( &ClientNetworkActivity::startNetworkActivity, this );
}

void ClientNetworkActivity::stop() noexcept
{
  cancellationRequested_.store( true );
}

void ClientNetworkActivity::startNetworkActivity()
{
  clientConnection_.connect();
  clientConnection_.login();

  // Temporary Hack
  clientConnection_.sendPlayerData( playerData_ );

  TickBuffer tickBuffer { playerData_ };

  clientConnection_.setSocketMode( ClientConnection::SocketIOMode::NonBlocking );

  // Main network loop
  while ( ! cancellationRequested_.load() )
  {
    // Do we need a sleep here?
    clientConnection_.sendTick();

    clientConnection_.receiveTick( tickBuffer );

    tickBuffer.processTicks();
  }

  isRunning_ = false;
}
