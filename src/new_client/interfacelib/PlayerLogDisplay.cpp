#include "PlayerLogDisplay.h"

#include <fstream>
#include <iostream>

#include "ColorPalette.h"
#include "ConstantIdentifiers.h"

namespace MenAmongGods
{
PlayerLogDisplay::PlayerLogDisplay()
    : sf::Transformable()
    , MenAmongGods::Component()
    , messageLog_()
    , charactersPerLine_( 48 )
    , chatLogOffset_( 0 )
{
}

void PlayerLogDisplay::update()
{
  // Do nothing for now.
}

void PlayerLogDisplay::onUserInput( const sf::Event& )
{

  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::PageUp ) )
  {
    if ( static_cast< int >( messageLog_.size() ) > ( chatLogOffset_ + 5 ) )
    {
      chatLogOffset_ += 5;
      recalculateMessagePositions();
    }
  }

  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::PageDown ) )
  {
    chatLogOffset_ == 0 ? chatLogOffset_ : chatLogOffset_ -= 5;
    recalculateMessagePositions();
  }
}

void PlayerLogDisplay::finalize()
{
  // Do nothing for now.
}

std::string PlayerLogDisplay::splitStringWithNewlines( const std::string& input, int lineCount )
{
  std::string output = input;
  for ( int i = 0; i < lineCount; ++i )
  {
    int offset = lineCount * charactersPerLine_;

    if ( offset >= static_cast< int >( input.length() ) )
    {
      break;
    }

    output.insert( lineCount * charactersPerLine_, "\n" );
  }

  return output + "\n";
}

void PlayerLogDisplay::recalculateMessagePositions()
{
  const sf::Vector2f startPosition { 500.0f, 224.0f };

  // Start at end of message list and work backwards from the start.
  unsigned int i = 1;
  for ( auto&& m = std::rbegin( messageLog_ ) + chatLogOffset_; m != std::rend( messageLog_ ); ++m )
  {
    if ( m >= std::rend( messageLog_ ) || m < std::rbegin( messageLog_ ) )
    {
      return;
    }

    std::string  textStr                = m->getString().toAnsiString();
    bool         stringContainsNewlines = std::find( std::begin( textStr ), std::end( textStr ), '\n' ) != textStr.end();
    int          lineCount              = static_cast< int >( textStr.length() / charactersPerLine_ );
    sf::Vector2f newPosition            = startPosition - sf::Vector2f { 0.0f, static_cast< float >( ( i + lineCount ) * FONT_SIZE ) };

    if ( lineCount > 0 && ! stringContainsNewlines )
    {
      textStr = splitStringWithNewlines( textStr, lineCount );
      m->setString( textStr );
      m->setLineSpacing( 0.8f );
    }

    // Need to handle the case where each message could take up multiple lines
    m->setPosition( newPosition );
    i += lineCount + 1;
  }
}

void PlayerLogDisplay::addMessage( const sf::Text& newMsg )
{
  messageLog_.push_back( newMsg );

  recalculateMessagePositions();
}

void PlayerLogDisplay::writeLogToFile( const std::string& pathToFile ) const
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

void PlayerLogDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  const float minimumYPosition = 3.0f;

  for ( auto&& msg = std::rbegin( messageLog_ ) + chatLogOffset_; msg != std::rend( messageLog_ ); msg++ )
  {
    // If we're already above what's going to be rendered
    // just break out early.    
    if ( msg >= std::rend( messageLog_ ) || msg < std::rbegin( messageLog_ ) || msg->getPosition().y < minimumYPosition )
    {
      return;
    }

    target.draw( *msg, states );
  }
}
} // namespace MenAmongGods