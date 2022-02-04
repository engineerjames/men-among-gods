#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

#include "JustifiableText.h"
#include "ResourceLocations.h"

int main()
{
  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  sf::Font font {};
  if ( ! font.loadFromFile( MenAmongGods::FONT_ROOT + "onuava.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
  };

  sf::Vector2f    justificationPoint { 400.0f, 300.0f };
  sf::CircleShape circle { 1.0f };
  circle.setFillColor( sf::Color::Green );
  circle.setPosition( justificationPoint );

  MenAmongGods::JustifiableText text { font, 12u, "Test justification" };
  text.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );
  text.setPosition( justificationPoint );

  while ( window.isOpen() )
  {
    sf::Event event;
    while ( window.pollEvent( event ) )
    {
      if ( event.type == sf::Event::Closed )
      {
        window.close();
      }
    }

    text.update();

    window.clear();
    window.draw( circle );
    window.draw( text );
    window.display();

    text.finalize();
  }

  return 0;
}