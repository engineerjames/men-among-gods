#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

int main()
{
  std::string pathToBackGround = "/home/jarmes/git/men-among-gods/src/new_client/gfx/bmp/00001.bmp";

  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  // Let's practice by loading the main ui
  sf::Image image {};
  if ( ! image.loadFromFile( pathToBackGround ) )
  {
    std::cerr << "Error loading main ui texture from file." << std::endl;
    return -1;
  }

  // Great, some images have masks of 254 0 254 as well
  image.createMaskFromColor( sf::Color { 0xFF00FFFF } );
  image.createMaskFromColor( sf::Color { 0xFE00FEFF } );

  sf::Texture texture {};
  texture.loadFromImage( image );

  sf::Sprite sprite { texture };

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

    window.clear();
    window.draw( sprite );
    window.display();
  }

  return 0;
}