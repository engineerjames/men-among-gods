#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

#include "../ConstantIdentifiers.h"
#include "../Map.h"
#include "../PlayerData.h"
#include "../TickBuffer.h"
#include "Component.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "MainUi.h"
#include "MapDisplay.h"

int main()
{
  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 10 );

  std::string path      = "gfx/gfx.zip";
  std::string indexPath = "gfx/gx00.idx";

  GraphicsCache cache {};
  cache.loadSprites( path, GraphicsCache::MAX_SPRITES );

  GraphicsIndex index { indexPath };
  index.load();

  sf::Clock clock {};
  sf::Time  time = clock.getElapsedTime();

  sf::Sprite bg = cache.getSprite( 1 );

  PlayerData pdata {};
  pdata.loadFromFile( "test/player.archive" );

  MenAmongGods::Map map {};
  TickBuffer        tickbuffer { pdata, map };

  auto mapPtr    = new MenAmongGods::MapDisplay( map, pdata, cache, index, tickbuffer );
  auto mainUiPtr = new MenAmongGods::MainUi( pdata, cache );

  mapPtr->loadFromFile( "test/mapfile.archive" );

  mainUiPtr->addMessage( MenAmongGods::MainUi::LogType::CHAT, "Mayest thou past the last gate." );
  mainUiPtr->addMessage( MenAmongGods::MainUi::LogType::LOG, "A new player has entered the game." );
  mainUiPtr->addMessage( MenAmongGods::MainUi::LogType::ERROR, "WARNING! This is an ERROR!!!" );
  mainUiPtr->addMessage( MenAmongGods::MainUi::LogType::INFO, "You have taken 12 damage." );

  std::vector< std::unique_ptr< MenAmongGods::Component > > components;

  components.emplace_back( mapPtr );
  components.emplace_back( mainUiPtr );

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
      mainUiPtr->addMessage( MenAmongGods::MainUi::LogType::LOG, "Periodic update test message." );
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