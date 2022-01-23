#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

#include "TextBox.h"
#include "TextInput.h"

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

  // Our test text box
  TextInput input {};

  // Our test message box
  TextBox textBox {};

  textBox.addMessage( TextBox::LogType::CHAT, "Mayest thou past the last gate." );
  textBox.addMessage( TextBox::LogType::LOG, "A new player has entered the game." );
  textBox.addMessage( TextBox::LogType::ERROR, "WARNING! This is an ERROR!!!" );
  textBox.addMessage( TextBox::LogType::INFO, "You have taken 12 damage." );

  input.setPosition( sf::Vector2f { 500.0f, 225.0f } );

  sf::Clock clock {};

  sf::Time time = clock.getElapsedTime();

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
          input.handleInput( event );
        }
      }
    }

    if ( ( clock.getElapsedTime() - time ).asSeconds() > 1.0f )
    {
      // Add new message
      textBox.addMessage( TextBox::LogType::LOG, "Periodic update test message." );
      time = clock.getElapsedTime();
    }

    window.clear();
    window.draw( sprite );
    window.draw( input );
    window.draw( textBox );
    window.display();
  }

  return 0;
}