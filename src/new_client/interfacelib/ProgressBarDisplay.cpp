#include "ProgressBarDisplay.h"

#include <limits>

namespace MenAmongGods
{

ProgressBarDisplay::ProgressBarDisplay( const sf::Vector2f& size )
    : backgroundRect_( size )
    , foregroundRect_( sf::Vector2f { size.y, 0 } )
    , percentComplete_( 0.0f )
    , isActive_( true )
{
  backgroundRect_.setFillColor( sf::Color::Blue );
  foregroundRect_.setFillColor( sf::Color::Green );
}

void ProgressBarDisplay::update()
{
  sf::Vector2f bgSize = backgroundRect_.getSize();
  foregroundRect_.setSize( sf::Vector2f { bgSize.x * ( percentComplete_ / 100.0f ), bgSize.y } );
}

void ProgressBarDisplay::setPercentComplete( float percentComplete )
{
  percentComplete_ = percentComplete;

  if ( percentComplete_ < 0.0f )
  {
    percentComplete_ = 0.0f;
  }

  if ( percentComplete_ >= ( 100.0f - std::numeric_limits< float >::epsilon() ) )
  {
    percentComplete_ = 100.0f;
  }
}

bool ProgressBarDisplay::isComplete() const
{
  return percentComplete_ >= ( 100.0f - std::numeric_limits< float >::epsilon() );
}

void ProgressBarDisplay::onUserInput( const sf::Event& )
{
}

void ProgressBarDisplay::finalize()
{
}

void ProgressBarDisplay::setActive( bool isActive )
{
  isActive_ = isActive;
}

void ProgressBarDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  if ( ! isActive_ )
  {
    return;
  }

  target.draw( backgroundRect_, states );
  target.draw( foregroundRect_, states );
}

void ProgressBarDisplay::setPosition( const sf::Vector2f& newPosition )
{
  backgroundRect_.setPosition( newPosition );
  foregroundRect_.setPosition( newPosition );
}

} // namespace MenAmongGods