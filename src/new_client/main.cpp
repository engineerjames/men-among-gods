#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ClientNetworkActivity.h"
#include "Component.h"
#include "ConstantIdentifiers.h"
#include "FontCache.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "LoginUi.h"
#include "MainUi.h"
#include "Map.h"
#include "MapDisplay.h"
#include "PlayerData.h"
#include "ResourceLocations.h"
#include "TickBuffer.h"

#include <memory>
#include <vector>

namespace
{
static const constexpr int FRAME_RATE_LIMIT = 10;
static const constexpr int LOGIN_FONT_SIZE  = 16;
} // namespace

int main()
{
  sf::RenderWindow window( sf::VideoMode( MODEX, MODEY ), "Men Among Gods - New Client" );
  window.setFramerateLimit( FRAME_RATE_LIMIT );
  window.requestFocus();

  std::string fontPath  = MenAmongGods::getFontRoot() + "onuava.ttf";
  std::string path      = MenAmongGods::getGfxRoot() + "gfx.zip";
  std::string indexPath = MenAmongGods::getGfxRoot() + "gx00.idx";

  auto fontCache = std::make_unique< MenAmongGods::FontCache >( fontPath );
  auto gfxCache  = std::make_unique< GraphicsCache >();
  auto idxCache  = std::make_unique< GraphicsIndex >( indexPath );

  gfxCache->loadSprites( path, GraphicsCache::MAX_SPRITES );
  idxCache->load();

  MenAmongGods::Map map {};
  PlayerData        playerData {};
  auto              tickBufferPtr = std::make_shared< TickBuffer >( playerData, map );
  auto              client        = std::make_shared< ClientNetworkActivity >( *tickBufferPtr, playerData, MHOST, MHOST_PORT );

  auto mapPtr     = std::make_shared< MenAmongGods::MapDisplay >( map, playerData, *gfxCache, *idxCache, window );
  auto mainUiPtr  = std::make_shared< MenAmongGods::MainUi >( playerData, *gfxCache, *fontCache );
  auto loginUiPtr = std::make_shared< MenAmongGods::LoginUi >( playerData, window, *fontCache, LOGIN_FONT_SIZE );

  // Populate components
  std::vector< std::shared_ptr< MenAmongGods::Component > > components;
  components.push_back( mapPtr );
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
        std::cerr << "Starting client communication!" << std::endl;
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
      std::vector< std::shared_ptr< MenAmongGods::ClientCommand > > commands = c->getCommands();
      commandList.insert( std::end( commandList ), std::begin( commands ), std::end( commands ) );
      c->clearCommands();
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
  }

  return 0;
}