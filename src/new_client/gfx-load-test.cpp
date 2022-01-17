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
  std::string                          path = "/home/jarmes/git/men-among-gods/src/new_client/gfx";
  std::vector< std::filesystem::path > imageFiles {};
  for ( const auto &entry : std::filesystem::recursive_directory_iterator( path ) )
  {
    if ( ! entry.path().has_extension() )
    {
      continue;
    }

    if ( entry.path().extension() == ".png" || entry.path().extension() == ".bmp" )
    {
      imageFiles.push_back( entry.path() );
    }
  }

  std::cout << "Found " << imageFiles.size() << " files." << std::endl;

  // Need to sort based on the numeric file name ALONE
  std::sort( std::begin( imageFiles ), std::end( imageFiles ),
             []( const std::filesystem::path &a, const std::filesystem::path &b )
             {
               return a.filename() < b.filename();
             } );

  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  std::array< sf::Image, 13708 >   images {};
  std::array< sf::Texture, 13708 > textures {};
  std::array< sf::Sprite, 13708 >  sprites {};

  for ( unsigned int i = 0; i < imageFiles.size(); ++i )
  {
    // Let's practice by loading the main ui
    sf::Image image {};
    if ( ! image.loadFromFile( imageFiles[ i ].string() ) )
    {
      std::cerr << "Error loading main ui texture from file." << std::endl;
      return -1;
    }
    else
    {
      if ( imageFiles[ i ].extension() == ".bmp" )
      {
        image.createMaskFromColor( sf::Color { 0xFF00FFFF } );
      }
      images[ i ] = image;

      sf::Texture texture {};
      texture.loadFromImage( images[ i ] );
      textures[ i ] = texture;

      sf::Sprite sprite { textures[ i ] };
      sprites[ i ] = sprite;
    }
  }

  std::cout << "Done loading sprites." << std::endl;

  // Need to implement log_system_data()
  // Also, look at rec_player and send_player--these are the main I/O pathways to the client
  while ( window.isOpen() )
  {
    sf::Event event;
    while ( window.pollEvent( event ) )
    {
      if ( event.type == sf::Event::Closed )
        window.close();
    }

    window.clear();
    window.draw( sprites[ 0 ] );
    window.display();
  }

  return 0;
}