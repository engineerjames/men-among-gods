#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Component.h"
#include "ConstantIdentifiers.h"
#include "FontCache.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "MainUi.h"
#include "Map.h"
#include "MapDisplay.h"
#include "PlayerData.h"
#include "ResourceLocations.h"
#include "TickBuffer.h"

int main()
{
  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 10 );

  std::string path      = MenAmongGods::getGfxRoot() + "gfx.zip";
  std::string indexPath = MenAmongGods::getGfxRoot() + "gx00.idx";

  auto cache = std::make_unique< GraphicsCache >();
  cache->loadSprites( path, GraphicsCache::MAX_SPRITES );

  GraphicsIndex index { indexPath };
  index.load();

  sf::Clock clock {};
  sf::Time  time = clock.getElapsedTime();

  sf::Sprite bg = cache->getSprite( 1 );

  PlayerData pdata {};
  pdata.loadFromFile( "test/player.archive" );

  MenAmongGods::Map map {};
  TickBuffer        tickbuffer { pdata, map };

  auto fontCache = std::make_unique< MenAmongGods::FontCache >( MenAmongGods::getFontRoot() + "onuava.ttf" );

  auto mapPtr    = new MenAmongGods::MapDisplay( map, pdata, *cache, index, tickbuffer, window );
  auto mainUiPtr = new MenAmongGods::MainUi( pdata, *cache, *fontCache );

  mapPtr->loadFromFile( "test/mapfile.archive" );

  mainUiPtr->addMessage( LogType::CHAT, "Mayest thou past the last gate." );
  mainUiPtr->addMessage( LogType::LOG, "A new player has entered the game." );
  mainUiPtr->addMessage( LogType::ERROR, "WARNING! This is an ERROR!!!" );
  mainUiPtr->addMessage( LogType::INFO, "You have taken 12 damage." );

  std::vector< std::unique_ptr< MenAmongGods::Component > > components;

  components.emplace_back( mapPtr );
  components.emplace_back( mainUiPtr );

  // Note: As the window is re-sized--the WindowSize parameter increases, while the ViewSize stays the same
  while ( window.isOpen() )
  {
    sf::Event event;
    while ( window.pollEvent( event ) )
    {
      if ( event.type == sf::Event::Closed )
      {
        window.close();
      }

      for ( auto& c : components )
      {
        c->onUserInput( event );
      }
    }

    for ( auto& c : components )
    {
      c->update();
    }

    if ( ( clock.getElapsedTime() - time ).asSeconds() > 4.0f )
    {
      // Add new message
      mainUiPtr->addMessage( LogType::LOG, "Periodic update test message." );
      time = clock.getElapsedTime();
    }

    window.clear();
    window.draw( *mapPtr );
    window.draw( bg );
    window.draw( *mainUiPtr );
    window.display();

    for ( auto& c : components )
    {
      c->finalize();
    }
  }

  return 0;
}