#include "MainUi.h"

#include <iostream>

#include "ColorPalette.h"
#include "GuiFormatters.h"
#include "UiPositions.h"

MainUi::MainUi()
    : font_()
    , goldDisplay_()
    , textualRank_()
    , avLabel_()
    , avValue_()
    , wvLabel_()
    , wvValue_()
    , expLabel_()
    , expValue_()
    , skillsAndAttributes_(font_)
    , msgBox_( font_ )
    , userInput_( font_ )
{
  goldDisplay_.setPosition( sf::Vector2f { MenAmongGods::goldDisplayPosition } );
  textualRank_.setPosition( sf::Vector2f { MenAmongGods::textualRankPosition } );
  userInput_.setPosition( sf::Vector2f { MenAmongGods::userInputPosition } );

  avLabel_.setPosition( sf::Vector2f { MenAmongGods::avLabelPosition } );
  avValue_.setPosition( sf::Vector2f { MenAmongGods::avValuePosition } );

  wvLabel_.setPosition( sf::Vector2f { MenAmongGods::wvLabelPosition } );
  wvValue_.setPosition( sf::Vector2f { MenAmongGods::wvValuePosition } );

  expLabel_.setPosition( sf::Vector2f { MenAmongGods::expLabelPosition } );
  expValue_.setPosition( sf::Vector2f { MenAmongGods::expValuePosition } );

  hpLabel_.setPosition( sf::Vector2f { MenAmongGods::hpLabelPosition } );
  hpCurrentValue_.setPosition( sf::Vector2f { MenAmongGods::hpCurrentValuePosition } );
  hpMaxValue_.setPosition( sf::Vector2f { MenAmongGods::hpMaxValuePosition } );

  endLabel_.setPosition( sf::Vector2f { MenAmongGods::endLabelPosition } );
  endCurrentValue_.setPosition( sf::Vector2f { MenAmongGods::endCurrentValuePosition } );
  endMaxValue_.setPosition( sf::Vector2f { MenAmongGods::endMaxValuePosition } );

  manaLabel_.setPosition( sf::Vector2f { MenAmongGods::manaLabelPosition } );
  manaCurrentValue_.setPosition( sf::Vector2f { MenAmongGods::manaCurrentValuePosition } );
  manaMaxValue_.setPosition( sf::Vector2f { MenAmongGods::manaMaxValuePosition } );

  // Temporarily hardcode the font
  if ( ! font_.loadFromFile( "/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman.ttf" ) )
  {
    std::cerr << "Unable to load font!" << std::endl;
  }

  goldDisplay_.setFont( font_ );
  textualRank_.setFont( font_ );
  avLabel_.setFont( font_ );
  avValue_.setFont( font_ );
  wvLabel_.setFont( font_ );
  wvValue_.setFont( font_ );
  expLabel_.setFont( font_ );
  expValue_.setFont( font_ );
  hpLabel_.setFont( font_ );
  hpCurrentValue_.setFont( font_ );
  hpMaxValue_.setFont( font_ );
  endLabel_.setFont( font_ );
  endCurrentValue_.setFont( font_ );
  endMaxValue_.setFont( font_ );
  manaLabel_.setFont( font_ );
  manaCurrentValue_.setFont( font_ );
  manaMaxValue_.setFont( font_ );

  goldDisplay_.setCharacterSize( msgBox_.getFontSize() );
  textualRank_.setCharacterSize( msgBox_.getFontSize() );
  avLabel_.setCharacterSize( msgBox_.getFontSize() );
  avValue_.setCharacterSize( msgBox_.getFontSize() );
  wvLabel_.setCharacterSize( msgBox_.getFontSize() );
  wvValue_.setCharacterSize( msgBox_.getFontSize() );
  expLabel_.setCharacterSize( msgBox_.getFontSize() );
  expValue_.setCharacterSize( msgBox_.getFontSize() );
  hpLabel_.setCharacterSize( msgBox_.getFontSize() );
  hpCurrentValue_.setCharacterSize( msgBox_.getFontSize() );
  hpMaxValue_.setCharacterSize( msgBox_.getFontSize() );
  endLabel_.setCharacterSize( msgBox_.getFontSize() );
  endCurrentValue_.setCharacterSize( msgBox_.getFontSize() );
  endMaxValue_.setCharacterSize( msgBox_.getFontSize() );
  manaLabel_.setCharacterSize( msgBox_.getFontSize() );
  manaCurrentValue_.setCharacterSize( msgBox_.getFontSize() );
  manaMaxValue_.setCharacterSize( msgBox_.getFontSize() );

  goldDisplay_.setFillColor( MenAmongGods::MsgYellow );
  textualRank_.setFillColor( MenAmongGods::MsgYellow );
  avLabel_.setFillColor( MenAmongGods::MsgYellow );
  avValue_.setFillColor( MenAmongGods::MsgYellow );
  wvLabel_.setFillColor( MenAmongGods::MsgYellow );
  wvValue_.setFillColor( MenAmongGods::MsgYellow );
  expLabel_.setFillColor( MenAmongGods::MsgYellow );
  expValue_.setFillColor( MenAmongGods::MsgYellow );
  hpLabel_.setFillColor( MenAmongGods::MsgYellow );
  hpCurrentValue_.setFillColor( MenAmongGods::MsgYellow );
  hpMaxValue_.setFillColor( MenAmongGods::MsgYellow );
  endLabel_.setFillColor( MenAmongGods::MsgYellow );
  endCurrentValue_.setFillColor( MenAmongGods::MsgYellow );
  endMaxValue_.setFillColor( MenAmongGods::MsgYellow );
  manaLabel_.setFillColor( MenAmongGods::MsgYellow );
  manaCurrentValue_.setFillColor( MenAmongGods::MsgYellow );
  manaMaxValue_.setFillColor( MenAmongGods::MsgYellow );

  goldDisplay_.setOutlineColor( sf::Color::Black );
  textualRank_.setOutlineColor( sf::Color::Black );
  avLabel_.setOutlineColor( sf::Color::Black );
  avValue_.setOutlineColor( sf::Color::Black );
  wvLabel_.setOutlineColor( sf::Color::Black );
  wvValue_.setOutlineColor( sf::Color::Black );
  expLabel_.setOutlineColor( sf::Color::Black );
  expValue_.setOutlineColor( sf::Color::Black );
  hpLabel_.setOutlineColor( sf::Color::Black );
  hpCurrentValue_.setOutlineColor( sf::Color::Black );
  hpMaxValue_.setOutlineColor( sf::Color::Black );
  endLabel_.setOutlineColor( sf::Color::Black );
  endCurrentValue_.setOutlineColor( sf::Color::Black );
  endMaxValue_.setOutlineColor( sf::Color::Black );
  manaLabel_.setOutlineColor( sf::Color::Black );
  manaCurrentValue_.setOutlineColor( sf::Color::Black );
  manaMaxValue_.setOutlineColor( sf::Color::Black );

  goldDisplay_.setString( "5g 52s" );
  textualRank_.setString( "Private" );
  avLabel_.setString( "Armor Value" );
  avValue_.setString( "0" );
  wvLabel_.setString( "Weapon Value" );
  wvValue_.setString( "0" );
  expLabel_.setString( "Experience" );
  expValue_.setString( MenAmongGods::addThousandsSeparator(12412125u) );
  hpLabel_.setString( "Hitpoints" );
  hpCurrentValue_.setString( "100" );
  hpMaxValue_.setString( "100" );
  endLabel_.setString( "Endurance" );
  endCurrentValue_.setString( "100" );
  endMaxValue_.setString( "100" );
  manaLabel_.setString( "Mana" );
  manaCurrentValue_.setString( "100" );
  manaMaxValue_.setString( "100" );
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
  target.draw( avLabel_, states );
  target.draw( avValue_, states );
  target.draw( wvLabel_, states );
  target.draw( wvValue_, states );
  target.draw( expLabel_, states );
  target.draw( expValue_, states );
  target.draw( hpLabel_, states );
  target.draw( hpCurrentValue_, states );
  target.draw( hpMaxValue_, states );
  target.draw( endLabel_, states );
  target.draw( endCurrentValue_, states );
  target.draw( endMaxValue_, states );
  target.draw( manaLabel_, states );
  target.draw( manaCurrentValue_, states );
  target.draw( manaMaxValue_, states );
  target.draw( skillsAndAttributes_, states );
}

void MainUi::handleInput( sf::Event e )
{
  userInput_.handleInput( e );
}