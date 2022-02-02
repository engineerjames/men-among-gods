#include "LoginUi.h"

namespace MenAmongGods
{
LoginUi::LoginUi( const sf::RenderWindow& window, const sf::Font& font )
    : nameLabel_( "Name:", font )
    , nameEntry_( window, font )
    , descriptionLabel_( "Description:", font )
    , descriptionEntry_( window, font )
    , raceSelection_()
    , sexSelection_()
{
  raceSelection_.emplace_back( font, "Harakim", 10.0f );
  raceSelection_.emplace_back( font, "Templar", 10.0f );
  raceSelection_.emplace_back( font, "Mercenary", 10.0f );

  sexSelection_.emplace_back( font, "Male", 10.0f );
  sexSelection_.emplace_back( font, "Female", 10.0f );

  // Set the Name and Description Boxes
  nameLabel_.setPosition( sf::Vector2f { 50.0f, 50.0f } );
  nameEntry_.setPosition( sf::Vector2f { 50.0f, 100.0f } );
  descriptionLabel_.setPosition( sf::Vector2f { 50.0f, 150.0f } );
  descriptionEntry_.setPosition( sf::Vector2f { 50.0f, 200.0f } );
}

void LoginUi::update()
{
}

void LoginUi::onUserInput( const sf::Event& e )
{
  nameEntry_.onUserInput( e );
  descriptionEntry_.onUserInput( e );

  for ( auto& r : raceSelection_ )
  {
    r.onUserInput( e );
  }

  for ( auto& s : sexSelection_ )
  {
    s.onUserInput( e );
  }
}

void LoginUi::finalize()
{
}

void LoginUi::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( nameLabel_, states );
  target.draw( nameEntry_, states );
  target.draw( descriptionLabel_, states );
  target.draw( descriptionEntry_, states );

  for ( const auto& r : raceSelection_ )
  {
    target.draw( r, states );
  }

  for ( const auto& s : sexSelection_ )
  {
    target.draw( s, states );
  }
}

} // namespace MenAmongGods