#include "PasswordTextInputDisplay.h"

#include "ColorPalette.h"

#include <iostream>
#include <sstream>

namespace MenAmongGods
{
PasswordTextInputDisplay::PasswordTextInputDisplay( const sf::RenderWindow& window, const sf::Font& font, unsigned int fontSize )
    : MenAmongGods::TextInputDisplay( window, font, fontSize )
{
}

void PasswordTextInputDisplay::onUserInput( const sf::Event& e )
{
  // Only want to act on text being entered--specifically ASCII characters
  if ( e.type == sf::Event::TextEntered && e.text.unicode < 128 && isSelected_ )
  {
    // Backspace key
    if ( e.text.unicode == 8 && ! backingText_.empty() )
    {
      backingText_ = backingText_.substr( 0, backingText_.size() - 1 );
    }
    else if ( backingText_.size() < maxCharacters_ && e.text.unicode != 8 && e.text.unicode != 13 )
    {
      backingText_ += e.text.unicode;
    }

    std::stringstream ss {};

    for ( unsigned int i = 0; i < backingText_.length(); ++i )
    {
      ss << "*";
    }

    text_.setString( ss.str() + "_" );
  }
  else if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    if ( boundingBox_.getGlobalBounds().contains( sf::Mouse::getPosition( window_ ).x, sf::Mouse::getPosition( window_ ).y ) )
    {
      isSelected_ = true;
    }
    else
    {
      isSelected_ = false;
    }
  }
}

} // namespace MenAmongGods