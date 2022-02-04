#include <iostream>

#include <SFML/Graphics.hpp>

#include "LoginUi.h"
#include "PlayerData.h"

int main()
{
  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  sf::Font font {};
  if ( ! font.loadFromFile( "fonts/onuava.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
  };

  PlayerData            playerData {};
  MenAmongGods::LoginUi loginUi { playerData, window, font, 16 };

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