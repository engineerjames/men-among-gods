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
#include "ResourceLocations.h"

int main()
{
  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  std::string path      = MenAmongGods::GFX_ROOT + "gfx.zip";
  std::string indexPath = MenAmongGods::GFX_ROOT + "gx00.idx";

  GraphicsCache cache {};
  cache.loadSprites( path, GraphicsCache::MAX_SPRITES );

  sf::Font font {};
  if ( ! font.loadFromFile( MenAmongGods::FONT_ROOT + "onuava.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
  };

  unsigned int index = 0;

  sf::Text text {};
  text.setFont( font );
  text.setString( std::to_string( index ) );
  text.setCharacterSize( 24 );
  text.setFillColor( sf::Color::Yellow );
  text.setPosition( sf::Vector2f { 800 / 2.0, 600 / 2.0 } );

  while ( window.isOpen() )
  {
    sf::Event event;
    while ( window.pollEvent( event ) )
    {
      if ( event.type == sf::Event::Closed )
      {
        window.close();
      }
      if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
      {
        index == 0 ? index : index--;
      }
      else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
      {
        index == GraphicsCache::MAX_ID ? index : index++;
      }
    }

    if ( cache.getSprite( index ).getTexture() == nullptr )
    {
      text.setString( std::to_string( index ) + " INVALID" );
    }
    else
    {
      text.setString( std::to_string( index ) );
    }

    window.clear();
    window.draw( cache.getSprite( index ) );
    window.draw( text );
    window.display();
  }

  return 0;
}