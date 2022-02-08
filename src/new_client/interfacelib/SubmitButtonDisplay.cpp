#include "SubmitButtonDisplay.h"

#include "UtilityFunctions.h"

namespace MenAmongGods
{
SubmitButtonDisplay::SubmitButtonDisplay( const sf::RenderWindow& window, const sf::Font& font, unsigned int fontSize,
                                          sf::Vector2f buttonSize )
    : window_( window )
    , buttonShape_( buttonSize )
    , buttonText_( "Submit", font, fontSize )
    , submitCallback_()
    , isActivated_( false )
    , isEnabled_( true )
{
  buttonText_.setFillColor( sf::Color::Black );
}

void SubmitButtonDisplay::setPosition( const sf::Vector2f& newPosition )
{
  buttonShape_.setPosition( newPosition );
  buttonText_.setPosition( sf::Vector2f { newPosition.x + 0.15f * buttonText_.getLocalBounds().width,
                                          newPosition.y + 0.33f * buttonShape_.getLocalBounds().height } );
}

void SubmitButtonDisplay::update()
{
  if ( ! isEnabled_ )
  {
    buttonShape_.setFillColor( sf::Color::Green );
  }
}

bool SubmitButtonDisplay::hasSubmitted() const
{
  return ! isEnabled_;
}

void SubmitButtonDisplay::setCallBack( std::function< void() > callBack )
{
  submitCallback_ = callBack;
}

void SubmitButtonDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    if ( buttonShape_.getGlobalBounds().contains( MenAmongGods::getNormalizedMousePosition( window_ ) ) )
    {
      if ( submitCallback_ != nullptr && isEnabled_ )
      {
        submitCallback_();
      }

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