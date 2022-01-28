#include "TextBox.h"

#include <fstream>
#include <iostream>

#include "../ConstantIdentifiers.h"
#include "ColorPalette.h"

TextBox::TextBox()
    : sf::Drawable()
    , sf::Transformable()
    , MenAmongGods::Component()
    , messageLog_()
{
}

void TextBox::update()
{
  // Do nothing for now.
}

void TextBox::onUserInput( const sf::Event& )
{
  // Do nothing for now.
}

void TextBox::finalize()
{
  // Do nothing for now.
}

void TextBox::addMessage( const sf::Text& newMsg )
{
  messageLog_.push_back( newMsg );

  const sf::Vector2f startPosition { 500.0f, 224.0f };

  // Start at end of message list and work backwards from the start.
  unsigned int i = 1;
  for ( auto&& m = std::rbegin( messageLog_ ); m != std::rend( messageLog_ ); ++m )
  {
    sf::Vector2f newPosition = startPosition - sf::Vector2f { 0.0f, static_cast< float >( i * FONT_SIZE ) };

    // Need to handle the case where each message could take up multiple lines
    m->setPosition( newPosition );
    ++i;
  }
}

void TextBox::writeLogToFile( const std::string& pathToFile ) const
{
  std::ofstream fs { pathToFile };

  if ( fs.is_open() )
  {
    for ( auto&& m : messageLog_ )
    {
      fs << m.getString().toAnsiString() << '\n';
    }
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