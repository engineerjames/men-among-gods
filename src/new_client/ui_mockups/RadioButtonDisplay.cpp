#include "RadioButtonDisplay.h"

namespace MenAmongGods
{
RadioButtonDisplay::RadioButtonDisplay( const sf::Font& font, const std::string& labelText, float circleRadius )
    : outerCircle_( circleRadius )
    , innerCircle_( circleRadius * 0.75f )
    , isSelected_( false )
    , labelText_( labelText, font )
{
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

void RadioButtonDisplay::onUserInput( const sf::Event& )
{
}

void RadioButtonDisplay::finalize()
{
}

} // namespace MenAmongGods