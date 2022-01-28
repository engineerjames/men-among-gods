#include "TextInput.h"

#include <iostream>

#include "../ConstantIdentifiers.h"
#include "ColorPalette.h"

TextInput::TextInput( const sf::Font& font )
    : sf::Text()
    , maxCharacters_( 45 )
    , font_( font )
    , text_()
    , commandList_()
{
  this->setFont( font_ );
  this->setCharacterSize( FONT_SIZE );
  this->setFillColor( MenAmongGods::MsgYellow );
  this->setOutlineColor( sf::Color::Black );
  this->setLetterSpacing( 1.0f );
  this->setString( "_" );
}

void TextInput::handleInput( sf::Event e )
{
  // Pessimistic check for now--who decides?
  if ( e.type != sf::Event::TextEntered )
  {
    return;
  }

  // Backspace key
  if ( e.text.unicode == 8 && ! text_.empty() )
  {
    text_ = text_.substr( 0, text_.size() - 1 );
  }
  else if ( text_.size() < maxCharacters_ && e.text.unicode != 8 )
  {
    text_ += e.text.unicode;
  }

  // Enter
  if ( e.text.unicode == 13 )
  {
    // Copy command into command list
    commandList_.push_back( text_ );
    text_.clear();
  }

  this->setString( text_ + "_" );
}

void TextInput::setPosition( const sf::Vector2f& newPosition )
{
  sf::Text::setPosition( newPosition );
}

void TextInput::getAndClearCommands( std::vector< std::string >& outList )
{
  for ( const auto& s : commandList_ )
  {
    outList.push_back( s );
  }

  commandList_.clear();
}
