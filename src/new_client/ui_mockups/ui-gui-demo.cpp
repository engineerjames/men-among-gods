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
#include "../PlayerData.h"
#include "../TickBuffer.h"
#include "Component.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "MainUi.h"
#include "Map.h"

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

  static int wntab[ 20 ] = { WN_HEAD, WN_CLOAK, WN_BODY, WN_ARMS, WN_NECK, WN_BELT, WN_RHAND, WN_LHAND, WN_RRING, WN_LRING,
                             WN_LEGS, WN_FEET,  0,       0,       0,       0,       0,        0,        0,        0 };

  std::vector< sf::Sprite > inventorySpritesToRender {};
  for ( unsigned int n = 0; n < 12; n++ )
  {
    if ( pdata.getClientSidePlayerInfo().worn[ wntab[ n ] ] != 0 )
    {
      sf::Sprite newSprite = cache.getSprite( pdata.getClientSidePlayerInfo().worn[ wntab[ n ] ] );
      newSprite.setPosition( sf::Vector2f { static_cast< float >( 303 + ( n % 2 ) * 35 ), static_cast< float >( 2 + ( n / 2 ) * 35 ) } );
      inventorySpritesToRender.push_back( newSprite );
    }
  }

  TickBuffer tickbuffer { pdata };

  auto mapPtr    = new MenAmongGods::Map( cache, index, tickbuffer );
  auto mainUiPtr = new MainUi();

  mapPtr->loadFromFile( "test/mapfile.archive" );

  mainUiPtr->addMessage( MainUi::LogType::CHAT, "Mayest thou past the last gate." );
  mainUiPtr->addMessage( MainUi::LogType::LOG, "A new player has entered the game." );
  mainUiPtr->addMessage( MainUi::LogType::ERROR, "WARNING! This is an ERROR!!!" );
  mainUiPtr->addMessage( MainUi::LogType::INFO, "You have taken 12 damage." );

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
      mainUiPtr->addMessage( MainUi::LogType::LOG, "Periodic update test message." );
      time = clock.getElapsedTime();
    }

    window.clear();
    window.draw( *mapPtr );
    window.draw( bg );
    window.draw( *mainUiPtr );
    for ( const auto& i : inventorySpritesToRender )
    {
      window.draw( i );
    }
    window.display();

    for ( auto& c : components )
    {
      c->finalize();
    }
  }

  return 0;
}