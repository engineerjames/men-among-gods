#include "ClientNetworkActivity.h"

#include <iostream>

#include "ConstantIdentifiers.h"

ClientNetworkActivity::~ClientNetworkActivity()
{
  if ( clientNetworkThread_.joinable() )
  {
    clientNetworkThread_.join();
  }
}

ClientNetworkActivity::ClientNetworkActivity( pdata &playerData, const std::string &hostIp, unsigned short hostPort )
    : clientNetworkThread_()
    , compressor_()
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
  playerData_.changed = 1;
  clientConnection_.sendPlayerData( playerData_ );

  while ( ! cancellationRequested_.load() )
  {
      // Main network loop
  }

  isRunning_ = false;
}