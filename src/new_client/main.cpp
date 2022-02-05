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

int main()
{
  sf::RenderWindow window( sf::VideoMode( MODEX, MODEY ), "Men Among Gods - New Client" );
  window.setFramerateLimit( 10 );
  window.requestFocus();

  std::string fontPath  = MenAmongGods::FONT_ROOT + "onuava.ttf";
  std::string path      = MenAmongGods::GFX_ROOT + "gfx.zip";
  std::string indexPath = MenAmongGods::GFX_ROOT + "gx00.idx";

  auto fontCache = std::make_unique< MenAmongGods::FontCache >( fontPath );
  auto gfxCache  = std::make_unique< GraphicsCache >();
  auto idxCache  = std::make_unique< GraphicsIndex >( indexPath );

  gfxCache->loadSprites( path, GraphicsCache::MAX_SPRITES );
  idxCache->load();

  MenAmongGods::Map map {};
  PlayerData        playerData {};
  auto              tickBufferPtr = std::make_shared< TickBuffer >( playerData, map );
  auto              client        = std::make_shared< ClientNetworkActivity >( *tickBufferPtr, playerData, MHOST, MHOST_PORT );

  auto mapPtr     = std::make_shared< MenAmongGods::MapDisplay >( map, playerData, *gfxCache, *idxCache, *tickBufferPtr, window );
  auto mainUiPtr  = std::make_shared< MenAmongGods::MainUi >( playerData, *gfxCache, *fontCache );
  auto loginUiPtr = std::make_shared< MenAmongGods::LoginUi >( playerData, window, *fontCache, 16 );

  // Populate components
  std::vector< std::shared_ptr< MenAmongGods::Component > > components;
  components.push_back( mapPtr );
  components.push_back( mainUiPtr );

  std::vector< std::shared_ptr< MenAmongGods::Component > > loginComponents;
  loginComponents.push_back( loginUiPtr );

  bool isLoggingIn                = true;
  bool hasKickStartedNetworkComms = false;

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

    sf::Event event;
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

    for ( auto& c : *currentComponents )
    {
      c->update();
    }

    window.clear();

    for ( auto& c : *currentComponents )
    {
      window.draw( *c );
    }

    window.display();

    for ( auto& c : *currentComponents )
    {
      c->finalize();
    }
  }

  return 0;
}