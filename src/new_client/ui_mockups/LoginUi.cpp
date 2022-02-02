#include "LoginUi.h"

namespace MenAmongGods
{
LoginUi::LoginUi( const sf::RenderWindow& window, const sf::Font& font, unsigned int fontSize )
    : nameLabel_( "Name:", font, fontSize )
    , nameEntry_( window, font, fontSize )
    , descriptionLabel_( "Description:", font, fontSize )
    , descriptionEntry_( window, font, fontSize )
    , passwordLabel_( "Password:", font, fontSize )
    , passwordEntry_( window, font, fontSize )
    , raceSelection_()
    , sexSelection_()
    , submitButton_( window, font, fontSize, sf::Vector2f { 75, 50 } )
    , components_()
{
  raceSelection_.emplace_back( window, font, "Harakim", 10.0f, fontSize );
  raceSelection_.emplace_back( window, font, "Templar", 10.0f, fontSize );
  raceSelection_.emplace_back( window, font, "Mercenary", 10.0f, fontSize );

  raceSelection_[ 0 ].setPosition( sf::Vector2f { 500.0f, 10.0f } );
  raceSelection_[ 1 ].setPosition( sf::Vector2f { 500.0f, 60.0f } );
  raceSelection_[ 2 ].setPosition( sf::Vector2f { 500.0f, 110.0f } );

  sexSelection_.emplace_back( window, font, "Male", 10.0f, fontSize );
  sexSelection_.emplace_back( window, font, "Female", 10.0f, fontSize );

  sexSelection_[ 0 ].setPosition( sf::Vector2f { 500.0f, 200.0f } );
  sexSelection_[ 1 ].setPosition( sf::Vector2f { 500.0f, 250.0f } );

  // Set the Name and Description Boxes
  nameLabel_.setPosition( sf::Vector2f { 10.0f, 10.0f } );
  nameEntry_.setPosition( sf::Vector2f { 10.0f, 35.0f } );
  passwordLabel_.setPosition( sf::Vector2f { 10.0f, 60.0f } );
  passwordEntry_.setPosition( sf::Vector2f { 10.0f, 85.0f } );
  descriptionLabel_.setPosition( sf::Vector2f { 10.0f, 115.0f } );
  descriptionEntry_.setPosition( sf::Vector2f { 10.0f, 140.0f } );

  // Set up the submit button
  submitButton_.setPosition( sf::Vector2f { 10.0f, 200.0f } );

  // Register components
  components_.push_back( &nameEntry_ );
  components_.push_back( &descriptionEntry_ );
  components_.push_back( &passwordEntry_ );
  components_.push_back( &submitButton_ );

  for ( auto& r : raceSelection_ )
  {
    components_.push_back( &r );
  }

  for ( auto& s : sexSelection_ )
  {
    components_.push_back( &s );
  }
}

void LoginUi::update()
{
  for ( auto& c : components_ )
  {
    c->update();
  }
}

void LoginUi::onUserInput( const sf::Event& e )
{
  for ( auto& c : components_ )
  {
    c->onUserInput( e );
  }
}

void LoginUi::finalize()
{
  for ( auto& c : components_ )
  {
    c->finalize();
  }
}

void LoginUi::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( nameLabel_, states );
  target.draw( descriptionLabel_, states );
  target.draw( passwordLabel_, states );

  for ( auto& c : components_ )
  {
    target.draw( *c, states );
  }
}

} // namespace MenAmongGods