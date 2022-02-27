#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ClientConfiguration.h"
#include "ClientNetworkActivity.h"
#include "Component.h"
#include "ConstantIdentifiers.h"
#include "FontCache.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "Logger.h"
#include "LoginUi.h"
#include "MainUi.h"
#include "Map.h"
#include "MapDisplay.h"
#include "PlayerData.h"
#include "ResourceLocations.h"
#include "SoundCache.h"
#include "TickBuffer.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

namespace
{
static const constexpr int LOGIN_FONT_SIZE = 16;
} // namespace

std::atomic< bool > shouldExit {};

int main()
{
  shouldExit.store( false );

  LOG_SET_LEVEL( MenAmongGods::ClientConfiguration::instance().loggingEnabled() );

  auto map        = std::make_unique< MenAmongGods::Map >();
  auto playerData = std::make_unique< PlayerData >();

  sf::RenderWindow window( sf::VideoMode( MODEX, MODEY ), "Men Among Gods - v1.1.2" );
  window.setFramerateLimit( MenAmongGods::ClientConfiguration::instance().frameLimit() );
  window.requestFocus();

  std::string fontPath  = MenAmongGods::getFontRoot() + "onuava.ttf";
  std::string path      = MenAmongGods::getGfxRoot() + "gfx.zip";
  std::string indexPath = MenAmongGods::getGfxRoot() + "gx00.idx";

  auto fontCache  = std::make_unique< MenAmongGods::FontCache >( fontPath );
  auto gfxCache   = std::make_unique< GraphicsCache >();
  auto idxCache   = std::make_unique< GraphicsIndex >( indexPath );
  auto soundCache = std::make_unique< SoundCache >();

  gfxCache->loadSprites( path, GraphicsCache::MAX_SPRITES );
  idxCache->load();
  soundCache->loadAudio( MenAmongGods::getSfxRoot() );

  auto tickBufferPtr = std::make_shared< TickBuffer >( *playerData, *map, *soundCache );
  auto client =
      std::make_shared< ClientNetworkActivity >( *tickBufferPtr, *playerData, MenAmongGods::ClientConfiguration::instance().hostIpAddress(),
                                                 MenAmongGods::ClientConfiguration::instance().hostPort() );

  auto mainUiPtr  = std::make_shared< MenAmongGods::MainUi >( window, *map, *playerData, *gfxCache, *idxCache, *fontCache );
  auto loginUiPtr = std::make_shared< MenAmongGods::LoginUi >( *playerData, window, *fontCache, LOGIN_FONT_SIZE );

  // Populate components
  std::vector< std::shared_ptr< MenAmongGods::Component > > components;
  components.push_back( mainUiPtr );

  std::vector< std::shared_ptr< MenAmongGods::Component > > loginComponents;
  loginComponents.push_back( loginUiPtr );

  bool isLoggingIn                = true;
  bool hasKickStartedNetworkComms = false;

  std::vector< std::shared_ptr< MenAmongGods::ClientCommand > > commandList {};

  while ( window.isOpen() )
  {
    std::vector< std::shared_ptr< MenAmongGods::Component > >* currentComponents = &components;
    if ( isLoggingIn && ! loginUiPtr->hasSubmitted() )
    {
      currentComponents = &loginComponents;
    }
    else
    {
      if ( ! hasKickStartedNetworkComms )
      {
        hasKickStartedNetworkComms = true;
        client->run();

        LOG_DEBUG( "Starting client communication!" );
      }
    }

    //
    // Process events--aka input by the user
    //
    sf::Event event {};
    while ( window.pollEvent( event ) )
    {
      if ( event.type == sf::Event::Closed )
      {
        window.close();
      }

      for ( auto& c : *currentComponents )
      {
        c->onUserInput( event );
      }
    }

    //
    // Run per-frame update logic
    //
    for ( auto& c : *currentComponents )
    {
      c->update();

      // Get all commands from components
      c->populateCommands( commandList );
    }

    // Pass off components to network-layer, and clear the command list for the next frame
    client->addClientCommands( commandList );
    commandList.clear();

    //
    // Draw stuff to the screen after clearing previous frame
    //
    window.clear();

    for ( auto& c : *currentComponents )
    {
      window.draw( *c );
    }

    window.display();

    //
    // Run finalization logic for all registered components
    //
    for ( auto& c : *currentComponents )
    {
      c->finalize();
    }

    if ( shouldExit.load() )
    {
      client->stop();
      break;
    }
  }

  playerData->saveToJsonFile( playerData->getPlayerName() );

  return 0;
}