#include <iostream>

#include <SFML/Graphics.hpp>

#include "FontCache.h"
#include "LoginUi.h"
#include "PlayerData.h"
#include "ResourceLocations.h"

int main()
{
  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  auto                  fontCache = std::make_unique< MenAmongGods::FontCache >( MenAmongGods::FONT_ROOT + "onuava.ttf" );
  PlayerData            playerData {};
  MenAmongGods::LoginUi loginUi { playerData, window, *fontCache, 16 };

  while ( window.isOpen() )
  {
    sf::Event event;
    while ( window.pollEvent( event ) )
    {
      if ( event.type == sf::Event::Closed )
      {
        window.close();
      }

      loginUi.onUserInput( event );
    }

    loginUi.update();

    window.clear();
    window.draw( loginUi );
    window.display();

    loginUi.finalize();
  }

  return 0;
}