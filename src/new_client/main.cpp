#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ClientNetworkActivity.h"
#include "ConstantIdentifiers.h"

int main()
{

  // playerSkillTab = static_cast< skilltab * >( malloc( sizeof( struct skilltab ) * 50 ) );
  // for ( int n = 0; n < 50; n++ )
  // {
  //   playerSkillTab[ n ]             = static_skilltab[ n ];
  //   playerSkillTab[ n ].attrib[ 0 ] = 1;
  // }

  sf::RenderWindow window( sf::VideoMode( MODEX, MODEY ), "Mercenaries of Astonia - New Client" );
  window.setFramerateLimit( 60 );

  pdata playerData {};

  auto client = std::make_unique< ClientNetworkActivity >( playerData, MHOST, MHOST_PORT );
  client->run();

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
    // window.draw(ourstuff);
    window.display();
  }

  return 0;
}