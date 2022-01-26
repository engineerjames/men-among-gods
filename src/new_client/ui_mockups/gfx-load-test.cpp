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
  sf::Clock                            clock {};
  sf::Time                             currentTime = clock.getElapsedTime();
  std::string                          path        = "/home/jarmes/git/men-among-gods/src/new_client/gfx";
  std::vector< std::filesystem::path > imageFiles {};
  for ( const auto& entry : std::filesystem::recursive_directory_iterator( path ) )
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
             []( const std::filesystem::path& a, const std::filesystem::path& b )
             {
               return a.filename() < b.filename();
             } );

  sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  static constexpr const std::size_t  N_IMAGES = 13708;
  std::array< sf::Image, N_IMAGES >   images {};
  std::array< sf::Texture, N_IMAGES > textures {};
  std::array< sf::Sprite, N_IMAGES >  sprites {};

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
      // Great, some images have masks of 254 0 254 as well
      image.createMaskFromColor( sf::Color { 0xFF00FFFF } );
      image.createMaskFromColor( sf::Color { 0xFE00FEFF } );

      images[ i ] = image;

      sf::Texture texture {};
      texture.loadFromImage( images[ i ] );
      textures[ i ] = texture;

      sf::Sprite sprite { textures[ i ] };
      sprites[ i ] = sprite;

      if ( i > 5000 )
      {
        break;
      }
    }

    // int percentComplete = i / static_cast< double >( N_IMAGES ) * 100.0;
    // std::cout << "Loading graphics data: " << percentComplete << "% complete.\r";
  }

  std::cout << std::endl;
  std::cout << "Done loading sprites." << std::endl;
  std::cerr << "Process took " << ( currentTime - clock.getElapsedTime() ).asSeconds() << std::endl;

  unsigned int index = 0;

  // Import font with which to draw the filename
  sf::Text text {};

  sf::Font font {};
  if ( ! font.loadFromFile( "/usr/share/fonts/truetype/msttcorefonts/Arial.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
  };
  text.setFont( font );
  text.setString( imageFiles[ index ].filename().generic_string() );
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
        index == 0 ? index = 0 : index--;
        text.setString( imageFiles[ index ].filename().generic_string() );
      }
      else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
      {
        index == imageFiles.size() - 1 ? imageFiles.size() - 1 : index++;
        text.setString( imageFiles[ index ].filename().generic_string() );
      }
    }

    window.clear();
    window.draw( sprites[ index ] );
    window.draw( text );
    window.display();
  }

  return 0;
}