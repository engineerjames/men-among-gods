#include "PlayerTextInputDisplay.h"

#include "ColorPalette.h"
#include "ConstantIdentifiers.h"
#include "SayCommand.h"

#include <iostream>

namespace MenAmongGods
{

PlayerTextInputDisplay::PlayerTextInputDisplay( const sf::Font& font )
    : MenAmongGods::Component()
    , drawableText_()
    , maxCharacters_( 45 )
    , font_( font )
    , text_()
    , history_()
{
  drawableText_.setFont( font_ );
  drawableText_.setCharacterSize( FONT_SIZE );
  drawableText_.setFillColor( MenAmongGods::MsgYellow );
  drawableText_.setOutlineColor( sf::Color::Black );
  drawableText_.setLetterSpacing( LETTER_SPACING );
  drawableText_.setString( "_" );
}

void PlayerTextInputDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( drawableText_, states );
}

void PlayerTextInputDisplay::update()
{
  // Do nothing for now
}

void PlayerTextInputDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Up ) )
  {
    text_ = history_.getPreviousCommand();
    drawableText_.setString( text_ + "_" );

    return;
  }
  else if ( e.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Down ) )
  {
    text_ = history_.getNextCommand();
    drawableText_.setString( text_ + "_" );

    return;
  }

  // Only want to act on text being entered--specifically ASCII characters
  if ( e.type != sf::Event::TextEntered || e.text.unicode >= 128 )
  {
    return;
  }

  // Backspace key
  if ( e.text.unicode == 8 && ! text_.empty() )
  {
    text_ = text_.substr( 0, text_.size() - 1 );
  } // Don't add control characters
  else if ( text_.size() < maxCharacters_ && e.text.unicode != 8 && e.text.unicode != 13 )
  {
    text_ += e.text.unicode;
  }

  // Enter
  if ( e.text.unicode == 13 )
  {
    // Copy command into command list
    commands_.emplace_back( std::make_shared< MenAmongGods::SayCommand >( text_ ) );
    history_.addCommand( text_ );
    text_.clear();
  }

  drawableText_.setString( text_ + "_" );
}

void PlayerTextInputDisplay::setPosition( const sf::Vector2f& newPosition )
{
  drawableText_.setPosition( newPosition );
}

void PlayerTextInputDisplay::finalize()
{
  // Do nothing for now
}
} // namespace MenAmongGods