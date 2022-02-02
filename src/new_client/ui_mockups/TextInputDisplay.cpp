#include "TextInputDisplay.h"

#include "ColorPalette.h"

#include <iostream>

namespace MenAmongGods
{
TextInputDisplay::TextInputDisplay( const sf::RenderWindow& window, const sf::Font& font )
    : window_( window )
    , text_( "", font )
    , isSelected_( false )
    , boundingBox_( sf::Vector2f { 100, 20 } )
    , backingText_()
    , maxCharacters_( 40 )
{
  text_.setOutlineColor( sf::Color::Black );
  text_.setFillColor( MenAmongGods::MsgYellow );
}

void TextInputDisplay::update()
{
  if ( isSelected_ )
  {
    boundingBox_.setOutlineColor( sf::Color::Blue );
    boundingBox_.setOutlineThickness( 5.0f );
  }
  else
  {
    boundingBox_.setOutlineColor( sf::Color::Black );
  }
}

void TextInputDisplay::deselect()
{
  isSelected_ = false;
}

void TextInputDisplay::onUserInput( const sf::Event& e )
{
  // Only want to act on text being entered--specifically ASCII characters
  if ( e.type == sf::Event::TextEntered && e.text.unicode >= 128 && isSelected_ )
  {
    // Backspace key
    if ( e.text.unicode == 8 && ! backingText_.empty() )
    {
      backingText_ = backingText_.substr( 0, backingText_.size() - 1 );
    }
    else if ( backingText_.size() < maxCharacters_ && e.text.unicode != 8 )
    {
      backingText_ += e.text.unicode;
    }
  }
  else if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    std::cerr << sf::Mouse::getPosition( window_ ).x << ", " << sf::Mouse::getPosition( window_ ).y << std::endl;
    std::cerr << boundingBox_.getGlobalBounds().left << ", " << boundingBox_.getGlobalBounds().top << std::endl;
    if ( boundingBox_.getGlobalBounds().contains( sf::Mouse::getPosition( window_ ).x, sf::Mouse::getPosition( window_ ).y ) )
    {
      isSelected_ = true;
      std::cerr << "IS SELECTED! " << std::endl;
    }
    else
    {
      isSelected_ = false;
      std::cerr << "Is deselected" << std::endl;
    }
  }
}

void TextInputDisplay::setPosition( sf::Vector2f newPosition )
{
  text_.setPosition( newPosition );
  boundingBox_.setPosition( newPosition );
}

void TextInputDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( boundingBox_, states );
  target.draw( text_, states );
}

void TextInputDisplay::finalize()
{
}

} // namespace MenAmongGods