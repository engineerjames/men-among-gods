#include "TextBox.h"

#include <iostream>

#include "ColorPalette.h"

TextBox::TextBox( const sf::Font& font )
    : sf::Drawable()
    , sf::Transformable()
    , maxCharactersPerLine_( 45 )
    , font_( font )
    , fontSize_( 12 )
    , messageLog_()
{
}

unsigned int TextBox::getFontSize() const
{
  return fontSize_;
}

void TextBox::addMessage( const sf::Text& newMsg )
{
  messageLog_.push_back( newMsg );

  const sf::Vector2f startPosition { 500.0f, 224.0f };

  // Start at end of message list and work backwards from the start.
  unsigned int i = 1;
  for ( auto&& m = std::rbegin( messageLog_ ); m != std::rend( messageLog_ ); ++m )
  {
    sf::Vector2f newPosition = startPosition - sf::Vector2f { 0.0f, static_cast< float >( i * fontSize_ ) };

    // Need to handle the case where each message could take up multiple lines
    m->setPosition( newPosition );
    ++i;
  }
}

void TextBox::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  const float minimumYPosition = 3.0f;

  for ( auto&& msg = std::rbegin( messageLog_ ); msg != std::rend( messageLog_ ); msg++ )
  {
    // If we're already above what's going to be rendered
    // just break out early.
    if ( msg->getPosition().y < minimumYPosition )
    {
      return;
    }

    target.draw( *msg, states );
  }
}