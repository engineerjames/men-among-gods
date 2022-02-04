#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ClientNetworkActivity.h"
#include "Component.h"
#include "ConstantIdentifiers.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "LoginUi.h"
#include "MainUi.h"
#include "Map.h"
#include "MapDisplay.h"
#include "PlayerData.h"
#include "TickBuffer.h"

#include <memory>
#include <vector>

int main()
{
  sf::RenderWindow window( sf::VideoMode( MODEX, MODEY ), "Men Among Gods - New Client" );
  window.setFramerateLimit( 10 );
  window.requestFocus();

  sf::Font font {};
  if ( ! font.loadFromFile( "ui_mockups/fonts/onuava.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
    return -1;
  }

  std::string path      = "ui_mockups/gfx/gfx.zip";
  std::string indexPath = "ui_mockups/gfx/gx00.idx";

  auto gfxCache = std::make_unique< GraphicsCache >();
  auto idxCache = std::make_unique< GraphicsIndex >( indexPath );

  gfxCache->loadSprites( path, GraphicsCache::MAX_SPRITES );
  idxCache->load();

  MenAmongGods::Map map {};
  PlayerData        playerData {};
  auto              tickBufferPtr = std::make_shared< TickBuffer >( playerData, map );
  auto              client        = std::make_shared< ClientNetworkActivity >( *tickBufferPtr, playerData, MHOST, MHOST_PORT );

  // client->run();

  auto mapPtr     = std::make_shared< MenAmongGods::MapDisplay >( map, playerData, *gfxCache, *idxCache, *tickBufferPtr, window );
  auto mainUiPtr  = std::make_shared< MenAmongGods::MainUi >( playerData, *gfxCache );
  auto loginUiPtr = std::make_shared< MenAmongGods::LoginUi >( playerData, window, font, 16 );

  // Populate components
  std::vector< std::shared_ptr< MenAmongGods::Component > > components;
  components.push_back( mapPtr );
  components.push_back( mainUiPtr );

  std::vector< std::shared_ptr< MenAmongGods::Component > > loginComponents;
  loginComponents.push_back( loginUiPtr );

  bool isLoggingIn = true;

  while ( window.isOpen() )
  {
    std::vector< std::shared_ptr< MenAmongGods::Component > >* currentComponents = &components;
    if ( isLoggingIn && ! loginUiPtr->hasSubmitted() )
    {
      currentComponents = &loginComponents;
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