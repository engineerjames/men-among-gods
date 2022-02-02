#include "RadioButtonDisplay.h"

namespace MenAmongGods
{
RadioButtonDisplay::RadioButtonDisplay( const sf::RenderWindow& window, const sf::Font& font, const std::string& labelText,
                                        float circleRadius, unsigned int fontSize )
    : window_( window )
    , outerCircle_( circleRadius, 60 )
    , innerCircle_( circleRadius * 0.75f, 60 )
    , isSelected_( false )
    , labelText_( labelText, font, fontSize )
{
  outerCircle_.setFillColor( sf::Color::White );
  innerCircle_.setFillColor( sf::Color::Black );
}

void RadioButtonDisplay::setPosition( const sf::Vector2f& newPosition )
{
  outerCircle_.setPosition( newPosition );
  innerCircle_.setPosition(
      sf::Vector2f { newPosition.x + 0.33f * innerCircle_.getRadius(), newPosition.y + 0.33f * innerCircle_.getRadius() } );

  // Position the label to the right, and mid-line ish with the diameter of the circle
  labelText_.setPosition(
      sf::Vector2f { newPosition.x + 2.5f * outerCircle_.getRadius(), newPosition.y + 0.20f * outerCircle_.getRadius() } );
}

void RadioButtonDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( outerCircle_, states );

  if ( isSelected_ )
  {
    target.draw( innerCircle_, states );
  }

  target.draw( labelText_, states );
}

void RadioButtonDisplay::update()
{
}

bool RadioButtonDisplay::isSelected() const
{
  return isSelected_;
}

void RadioButtonDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    if ( outerCircle_.getGlobalBounds().contains( sf::Mouse::getPosition( window_ ).x, sf::Mouse::getPosition( window_ ).y ) )
    {
      isSelected_ = true;
    }
    else
    {
      isSelected_ = false;
    }
  }
}

void RadioButtonDisplay::finalize()
{
}

} // namespace MenAmongGods