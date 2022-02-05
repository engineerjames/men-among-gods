#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

#include "ProgressBarDisplay.h"
#include "ResourceLocations.h"

int main()
{
  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  sf::Font font {};
  if ( ! font.loadFromFile( MenAmongGods::getFontRoot() + "onuava.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
  };

  MenAmongGods::ProgressBarDisplay progBar { sf::Vector2f { 500, 25 } };
  progBar.setPosition( sf::Vector2f { 50, 300 } );

  float percentComplete = 0.0f;
  while ( window.isOpen() )
  {
    sf::Event event;
    while ( window.pollEvent( event ) )
    {
      if ( event.type == sf::Event::Closed )
      {
        window.close();
      }
      else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
      {
        percentComplete -= 1.0f;
      }
      else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
      {
        percentComplete += 1.0f;
      }
    }

    progBar.setPercentComplete( percentComplete );

    progBar.update();

    window.clear();
    window.draw( progBar );
    window.display();

    progBar.finalize();
  }

  return 0;
}