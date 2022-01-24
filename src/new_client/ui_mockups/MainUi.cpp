#include "MainUi.h"

#include <iostream>

#include "ColorPalette.h"

MainUi::MainUi()
    : goldDisplay_()
    , textualRank_()
    , font_()
    , msgBox_( font_ )
    , userInput_( font_ )
{
  goldDisplay_.setPosition( sf::Vector2f { 452.0f, 188.0f } );
  textualRank_.setPosition( sf::Vector2f { 396.0f, 171.0f } );
  userInput_.setPosition( sf::Vector2f { 500.0f, 225.0f } );

  // Temporarily hardcode the font
  if ( ! font_.loadFromFile( "/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
  }

  goldDisplay_.setFont( font_ );
  textualRank_.setFont( font_ );
}

void MainUi::addMessage( LogType type, std::string text )
{
  sf::Text  newMsg { text, font_, msgBox_.getFontSize() };
  sf::Color messageColor {};

  switch ( type )
  {
  case LogType::CHAT:
    messageColor = MenAmongGods::MsgBlue;
    break;
  case LogType::LOG:
    messageColor = MenAmongGods::MsgGreen;
    break;
  case LogType::ERROR:
    messageColor = MenAmongGods::MsgRed;
    break;
  case LogType::INFO:
    messageColor = MenAmongGods::MsgYellow;
    break;
  default:
    messageColor = sf::Color::Blue;
    break;
  }

  newMsg.setFillColor( messageColor );
  newMsg.setOutlineColor( sf::Color::Black );
  newMsg.setLetterSpacing( 1.5f );

  msgBox_.addMessage( newMsg );
}

void MainUi::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( goldDisplay_, states );
  target.draw( textualRank_, states );
  target.draw( msgBox_, states );
  target.draw( userInput_, states );
}

void MainUi::handleInput( sf::Event e )
{
  userInput_.handleInput( e );
}