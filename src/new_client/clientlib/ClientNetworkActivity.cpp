#include "ClientNetworkActivity.h"

#include <atomic>
#include <cstring>

#include "ClientConfiguration.h"
#include "ClientMessage.h"
#include "Logger.h"
#include "Map.h"
#include "PlayerData.h"
#include "TickBuffer.h"

// Commands
#include "AutoLookCommand.h"

ClientNetworkActivity::ClientNetworkActivity( TickBuffer& tickBuffer, PlayerData& playerData, const std::string& hostIp,
                                              unsigned short hostPort )
    : clientConnection_( hostIp, hostPort )
    , playerData_( playerData )
    , tickBuffer_( tickBuffer )
    , commands_()
{
}

void ClientNetworkActivity::addClientCommands( const std::vector< std::shared_ptr< MenAmongGods::ClientCommand > >& commandList )
{
  // No need to append commands if the vector is empty
  if ( commandList.empty() )
  {
    return;
  }

    LOG_DEBUG( "Adding " << commandList.size() << " commands to network thread." );

  // Insert new commands to the end of the command list
  commands_.insert( std::end( commands_ ), std::begin( commandList ), std::end( commandList ) );
}

void ClientNetworkActivity::login() noexcept
{
  bool connectionSuccessful = clientConnection_.connect();

  if ( ! connectionSuccessful )
  {
    LOG_ERROR( "Unable to establish connection." );
    return;
  }

  bool loginSuccessful = clientConnection_.login( playerData_ );

  if ( ! loginSuccessful )
  {
    LOG_ERROR( "Unable to login." );
    return;
  }

  bool sendPlayerInfoSuccessful = clientConnection_.sendPlayerData( playerData_ );

  if ( ! sendPlayerInfoSuccessful )
  {
    LOG_ERROR( "Unable to send player information." );
    return;
  }

  clientConnection_.sendHardwareInfo();
  clientConnection_.setSocketMode( ClientConnection::SocketIOMode::NonBlocking );
}

void ClientNetworkActivity::processServerTicks() noexcept
{
  sf::Time now = clock_.getElapsedTime();

  if ( ( now - timeSinceLastTickSent_ ).asSeconds() > 0.75f )
  {
    if ( ! clientConnection_.sendTick() )
    {
      LOG_ERROR( "Unable to send tick!" );
    }
    // Reset timeSinceLastTickSent
    timeSinceLastTickSent_ = clock_.getElapsedTime();
  }

  if ( ! clientConnection_.receiveTick( tickBuffer_ ) )
  {
    LOG_ERROR( "Unable to receive tick!" );
  }

  tickBuffer_.processTicks();
}

void ClientNetworkActivity::sendCommands() noexcept
{
  for ( const auto& c : commands_ )
  {
    clientConnection_.processCommand( c );
  }
  commands_.clear();

  clientConnection_.getUnknownPlayerIds( playerData_ );
}