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

  PlayerData pdata {};

  pdata.loadFromFile( "/home/jarmes/git/men-among-gods/src/new_client/ui_mockups/player.archive" );
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
    for ( const auto& i : inventorySpritesToRender )
    {
      window.draw( i );
    }
    window.display();
  }

  return 0;
}