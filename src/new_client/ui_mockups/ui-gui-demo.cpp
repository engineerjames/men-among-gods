#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "MainUi.h"
#include "Map.h"

int main()
{
  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  std::string path      = "/home/jarmes/git/men-among-gods/src/new_client/gfx/gfx.zip";
  std::string indexPath = "/home/jarmes/git/men-among-gods/src/new_client/ui_mockups/gx00.idx";

  GraphicsCache cache {};
  cache.loadSprites( path, GraphicsCache::MAX_SPRITES );

  GraphicsIndex index { indexPath };
  index.load();

  MainUi mainui {};

  mainui.addMessage( MainUi::LogType::CHAT, "Mayest thou past the last gate." );
  mainui.addMessage( MainUi::LogType::LOG, "A new player has entered the game." );
  mainui.addMessage( MainUi::LogType::ERROR, "WARNING! This is an ERROR!!!" );
  mainui.addMessage( MainUi::LogType::INFO, "You have taken 12 damage." );

  sf::Clock clock {};

  sf::Time time = clock.getElapsedTime();

  MenAmongGods::Map map { cache, index };
  map.loadFromFile( "/home/jarmes/git/men-among-gods/src/new_client/ui_mockups/mapfile.archive" );

  sf::Sprite bg = cache.getSprite( 1 );

  while ( window.isOpen() )
  {
    sf::Event event;
    while ( window.pollEvent( event ) )
    {
      if ( event.type == sf::Event::Closed )
      {
        window.close();
      }

      if ( event.type == sf::Event::TextEntered )
      {
        if ( event.text.unicode < 128 ) // ASCII only
        {
          mainui.handleInput( event );
        }
      }
    }

    if ( ( clock.getElapsedTime() - time ).asSeconds() > 1.0f )
    {
      // Add new message
      mainui.addMessage( MainUi::LogType::LOG, "Periodic update test message." );
      time = clock.getElapsedTime();
    }

    window.clear();
    window.draw( map );
    window.draw( bg );
    window.draw( mainui );
    window.display();
  }

  return 0;
}