#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ClientConfiguration.h"
#include "ClientNetworkActivity.h"
#include "Component.h"
#include "Constants.h"
#include "FontCache.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "Logger.h"
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
static const constexpr int MODEX           = 800;
static const constexpr int MODEY           = 600;
} // namespace

int main( int argc, char** args )
{
  LOG_SET_LEVEL( MenAmongGods::ClientConfiguration::instance().loggingEnabled() );

  // Amiko-Regular is a great choice
  // BP-Mono looks decent, would need some tweaks--at least it is a serif font
  std::string fontPath  = MenAmongGods::getFontRoot() + "Amiko-Regular.ttf";
  std::string path      = MenAmongGods::getGfxRoot() + "gfx.zip";
  std::string indexPath = MenAmongGods::getGfxRoot() + "gx00.idx";

  auto fontCache  = std::make_unique< MenAmongGods::FontCache >( fontPath );
  auto gfxCache   = std::make_unique< GraphicsCache >();
  auto idxCache   = std::make_unique< GraphicsIndex >( indexPath );
  auto soundCache = std::make_unique< SoundCache >();

  sf::RenderWindow window( sf::VideoMode( MODEX, MODEY ), "Men Among Gods - v1.1.6" );
  window.setFramerateLimit( CLIENT_FRAME_LIMIT );
  window.requestFocus();

  auto map        = std::make_unique< MenAmongGods::Map >();
  auto playerData = std::make_shared< PlayerData >( window, *fontCache );

  if ( argc >= 3 )
  {
    if ( std::string( args[ 1 ] ) == "moafile" )
    {
      LOG_DEBUG( "Loading into client via moafile" );
      // Loading via moafile
      playerData->loadFromJsonFile( std::string( args[ 2 ] ) );
      playerData->setPassword( std::string( args[ 3 ] ) );
    }
    else if ( std::string( args[ 1 ] ) == "newentry" )
    {
      LOG_DEBUG( "Loading into client via a new character entry" );

      Json::Reader reader {};
      Json::Value  root {};
      reader.parse( args[ 2 ], root );

      playerData->fromJson( root );
    }
  }
  else
  {
    return -1;
  }

  idxCache->load();
  soundCache->loadAudio( MenAmongGods::getSfxRoot() );
  gfxCache->loadNewGfxCache();

  auto tickBufferPtr = std::make_shared< TickBuffer >( *playerData, *map, *soundCache );
  auto client =
      std::make_shared< ClientNetworkActivity >( *tickBufferPtr, *playerData, MenAmongGods::ClientConfiguration::instance().hostIpAddress(),
                                                 MenAmongGods::ClientConfiguration::instance().hostPort() );

  auto mainUiPtr = std::make_shared< MenAmongGods::MainUi >( window, *map, *playerData, *gfxCache, *idxCache, *fontCache );

  // Populate components
  std::vector< std::shared_ptr< MenAmongGods::Component > > components {};
  components.push_back( mainUiPtr );
  components.push_back( playerData );

  std::vector< std::shared_ptr< MenAmongGods::ClientCommand > > commandList {};

  auto errMessage = client->login();
  if ( errMessage.has_value() )
  {
    std::cerr << errMessage.value() << std::endl;
    return -1;
  }

  // TODO: Eventually we'll add an optional FPS display for testing only

  while ( window.isOpen() )
  {
    //
    // Process events--aka input by the user
    //
    sf::Event event {};
    while ( window.pollEvent( event ) )
    {
      if ( event.type == sf::Event::Closed )
      {
        if ( playerData->getExitFlag() )
        {
          window.close();
        }
        else
        {
          playerData->addLogMessage(
              LogType::ERROR,
              "You must exit the game through the tavern! Or the EXIT button in the lower right hand corner of the screen" );
        }
      }

      for ( auto& c : components )
      {
        c->onUserInput( event );
      }

      // User request to modify sound volume (TODO: Move later)
      if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::F2 ) )
      {
        soundCache->increaseVolume();
      }

      if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::F1 ) )
      {
        soundCache->decreaseVolume();
      }
    }

    //
    // Run per-frame update logic
    //
    for ( auto& c : components )
    {
      c->update();

      // Get all commands from components
      c->populateCommands( commandList );
    }

    // Pass off components to network-layer, and clear the command list for the next frame
    client->addClientCommands( commandList );
    commandList.clear();

    client->processServerTicks();

    client->sendCommands();

    //
    // Draw stuff to the screen after clearing previous frame
    //
    window.clear();

    for ( auto& c : components )
    {
      window.draw( *c );
    }

    window.display();

    //
    // Run finalization logic for all registered components
    //
    for ( auto& c : components )
    {
      c->finalize();
    }
  }

  playerData->saveToJsonFile( playerData->getPlayerName() );

  return 0;
}