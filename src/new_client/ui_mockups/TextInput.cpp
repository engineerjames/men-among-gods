#include "TextInput.h"

#include <iostream>

TextInput::TextInput()
    : sf::Text()
    , maxCharacters_( 45 )
    , font_()
    , text_()
    , commandList_()
{
  // Temporarily hardcode the font
  if ( ! font_.loadFromFile( "/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
  };

  this->setFont( font_ );
  this->setCharacterSize( 12 );
  this->setFillColor( sf::Color::Yellow );
  this->setOutlineColor( sf::Color::Black );
  this->setLetterSpacing( 1.5f );
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

  this->setString( text_ );
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
