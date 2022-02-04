#include "ClientNetworkActivity.h"

#include <cstring>
#include <iostream>

#include "ClientMessage.h"
#include "ConstantIdentifiers.h"
#include "Map.h"
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

ClientNetworkActivity::ClientNetworkActivity( TickBuffer& tickBuffer, PlayerData& playerData, const std::string& hostIp,
                                              unsigned short hostPort )
    : clientNetworkThread_()
    , clientConnection_( hostIp, hostPort )
    , cancellationRequested_( false )
    , isRunning_( false )
    , playerData_( playerData )
    , tickBuffer_( tickBuffer )
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
  if ( ! isRunning_ )
  {
    return;
  }

  cancellationRequested_.store( true );
}

void ClientNetworkActivity::startNetworkActivity()
{
  clientConnection_.connect();
  clientConnection_.login();

  clientConnection_.sendPlayerData( playerData_ );

  clientConnection_.sendHardwareInfo();

  clientConnection_.setSocketMode( ClientConnection::SocketIOMode::NonBlocking );

  sf::Clock clock {};
  sf::Time  timeSinceLastTickSent = clock.getElapsedTime();

  // Filthy hack to have the character move once to populate map fully.
  static bool hasMoved = false;

  // Main network loop
  while ( ! cancellationRequested_.load() )
  {
    sf::Time now = clock.getElapsedTime();
    if ( ( now - timeSinceLastTickSent ).asSeconds() > 1.0f )
    {
      if ( ! clientConnection_.sendTick() )
      {
        std::cerr << "Unable to send tick!" << std::endl;
      }
      // Reset timeSinceLastTickSent
      timeSinceLastTickSent = clock.getElapsedTime();
    }

    if ( ! clientConnection_.receiveTick( tickBuffer_ ) )
    {
      std::cerr << "Unable to receive tick!" << std::endl;
    }

    tickBuffer_.processTicks();

    if ( ! hasMoved )
    {
      std::cerr << "Moving!" << std::endl;
      clientConnection_.moveOnce();
      hasMoved = true;
    }
  }

  isRunning_ = false;
}