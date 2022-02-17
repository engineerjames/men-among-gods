#include "JustifiableText.h"

#include "Logger.h"

namespace MenAmongGods
{

JustifiableText::JustifiableText()
    : MenAmongGods::Component()
    , text_()
    , positionNeedsUpdating_( true )
    , justificationMode_( TextJustification::LEFT )
    , cachedPosition_()
    , centerWidth_()
{
}

JustifiableText::JustifiableText( const sf::Font& font, unsigned int characterSize, std::string initialText )
    : MenAmongGods::Component()
    , text_( initialText, font, characterSize )
    , positionNeedsUpdating_( true )
    , justificationMode_( TextJustification::LEFT )
    , cachedPosition_()
    , centerWidth_()
{
  text_.setFont( font );
}

void JustifiableText::setOutlineColor( const sf::Color& color )
{
  text_.setOutlineColor( color );
}

void JustifiableText::setFillColor( const sf::Color& color )
{
  text_.setFillColor( color );
}

void JustifiableText::setFont( const sf::Font& font )
{
  text_.setFont( font );
}

void JustifiableText::setCharacterSize( unsigned int size )
{
  text_.setCharacterSize( size );
}

void JustifiableText::setCenterWidth( int newValue )
{
  centerWidth_ = newValue;
}

void JustifiableText::setString( const std::string& text )
{
  if ( text != text_.getString() )
  {
    text_.setString( text );
    positionNeedsUpdating_ = true;
  }
}

void JustifiableText::update()
{
  if ( ! positionNeedsUpdating_ )
  {
    // Do nothing!
    return;
  }

  moveTextAccordingToJustification();
}

void JustifiableText::onUserInput( const sf::Event& )
{
}

void JustifiableText::setJustification( JustifiableText::TextJustification mode )
{
  justificationMode_ = mode;
}

void JustifiableText::moveTextAccordingToJustification()
{
  sf::FloatRect boundingBox = text_.getLocalBounds();

  if ( justificationMode_ == TextJustification::LEFT )
  {
    return;
  }
  else if ( justificationMode_ == TextJustification::RIGHT )
  {
    text_.setPosition( sf::Vector2f { cachedPosition_.x - boundingBox.width, cachedPosition_.y } );
  }
  else if ( justificationMode_ == TextJustification::CENTER )
  {
    float newXPosition = ( ( centerWidth_ - boundingBox.width ) / 2.0f ) + cachedPosition_.x;
    text_.setPosition( sf::Vector2f { newXPosition, cachedPosition_.y } );
  }
}

void JustifiableText::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( text_, states );
}

void JustifiableText::setPosition( sf::Vector2f newPosition )
{
  cachedPosition_ = newPosition;
}

// Finalize is called once at the end of every frame
void JustifiableText::finalize()
{
}

} // namespace MenAmongGods