#include "TextBox.h"

#include <iostream>

TextBox::TextBox()
    : sf::Drawable()
    , sf::Transformable()
    , maxCharactersPerLine_( 45 )
    , font_()
    , fontSize_( 12 )
    , messageLog_()
{
  // Temporarily hardcode the font
  if ( ! font_.loadFromFile( "/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
  }

  // 500,3 is upper left hand corner
  // 500,224 is lower left hand corner
}

void TextBox::addMessage( LogType type, std::string text )
{
  messageLog_.emplace_back( text, font_, fontSize_ );

  auto newMessage = messageLog_.end() - 1;

  sf::Color messageColor {};

  switch ( type )
  {
  case LogType::CHAT:
    messageColor = sf::Color::Blue;
    break;
  case LogType::LOG:
    messageColor = sf::Color::Green;
    break;
  case LogType::ERROR:
    messageColor = sf::Color::Red;
    break;
  case LogType::INFO:
    messageColor = sf::Color::Yellow;
    break;
  default:
    messageColor = sf::Color::Blue;
    break;
  }

  newMessage->setFillColor( messageColor );
  newMessage->setOutlineColor( sf::Color::Black );
  newMessage->setLetterSpacing( 1.5f );
}

void TextBox::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  const sf::Vector2f startPosition { 500.0f, 224.0f };
  const float        minimumYPosition = 3.0f;

  // Start at end of message list and work backwards from the start.
  unsigned int i = 1; // Fix this offset
  for ( auto&& m = std::rbegin( messageLog_ ); m != std::rend( messageLog_ ); ++m )
  {
    sf::Vector2f newPosition = startPosition - sf::Vector2f { 0.0f, static_cast< float >( i * fontSize_ ) };

    if ( newPosition.y < minimumYPosition )
    {
      return;
    }

    // Need to handle the case where each message could take up multiple lines
    m->setPosition( newPosition );
    target.draw( *m, states );
    ++i;
  }
}