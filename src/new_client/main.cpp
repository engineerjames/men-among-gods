#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ClientNetworkActivity.h"
#include "ConstantIdentifiers.h"
#include "Map.h"
#include "PlayerData.h"

int main()
{

  sf::RenderWindow window( sf::VideoMode( MODEX, MODEY ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  MenAmongGods::Map map {};
  PlayerData        playerData {};

  auto client = std::make_unique< ClientNetworkActivity >( playerData, map, MHOST, MHOST_PORT );
  client->run();

  while ( window.isOpen() )
  {
    sf::Event event;
    while ( window.pollEvent( event ) )
    {
      if ( event.type == sf::Event::Closed )
        window.close();
    }

    window.clear();
    // window.draw(ourstuff);
    window.display();
  }

  return 0;
}