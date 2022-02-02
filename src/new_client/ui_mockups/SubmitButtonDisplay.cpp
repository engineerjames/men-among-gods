#include "SubmitButtonDisplay.h"

namespace MenAmongGods
{
SubmitButtonDisplay::SubmitButtonDisplay( const sf::RenderWindow& window, const sf::Font& font, unsigned int fontSize,
                                          sf::Vector2f buttonSize )
    : window_( window )
    , buttonShape_( buttonSize )
    , buttonText_( "Submit", font, fontSize )
    , isActivated_( false )
    , isEnabled_( true )
{
  buttonText_.setFillColor( sf::Color::Black );
}

void SubmitButtonDisplay::setPosition( const sf::Vector2f& newPosition )
{
  buttonShape_.setPosition( newPosition );
  buttonText_.setPosition( sf::Vector2f { newPosition.x + 0.25f * buttonText_.getLocalBounds().width,
                                          newPosition.y + 0.25f * buttonShape_.getLocalBounds().height } );
}

void SubmitButtonDisplay::update()
{
}

void SubmitButtonDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    if ( buttonShape_.getGlobalBounds().contains( sf::Mouse::getPosition( window_ ).x, sf::Mouse::getPosition( window_ ).y ) )
    {
      isActivated_ = true;
      isEnabled_   = false;
    }
  }
}

void SubmitButtonDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( buttonShape_, states );
  target.draw( buttonText_, states );
}

void SubmitButtonDisplay::finalize()
{
}

} // namespace MenAmongGods