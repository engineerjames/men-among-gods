#include "PlayerLogDisplay.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "ColorPalette.h"
#include "UiConstants.h"
#include "UtilityFunctions.h"

namespace MenAmongGods
{
PlayerLogDisplay::PlayerLogDisplay( const sf::RenderWindow& window )
    : sf::Transformable()
    , MenAmongGods::Component()
    , window_( window )
    , messageLog_()
    , charactersPerLine_( 52 )
    , chatLogOffset_( 0 )
{
}

void PlayerLogDisplay::update()
{
  // Do nothing for now.
}

void PlayerLogDisplay::onUserInput( const sf::Event& e )
{
  bool         scrolledDown  = false;
  bool         scrolledUp    = false;
  sf::Vector2f mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );

  if ( e.type == sf::Event::MouseWheelScrolled && MenAmongGods::chatLogBoundingBox.contains( mousePosition ) )
  {
    if ( e.mouseWheelScroll.delta > 0 )
    {
      scrolledUp = true;
    }
    else if ( e.mouseWheelScroll.delta < 0 )
    {
      scrolledDown = true;
    }
  }

  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::PageUp ) || scrolledUp )
  {
    if ( static_cast< int >( messageLog_.size() ) > ( chatLogOffset_ + 5 ) )
    {
      chatLogOffset_ += 5;
      recalculateMessagePositions();
    }
  }

  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::PageDown ) || scrolledDown )
  {
    chatLogOffset_ == 0 ? chatLogOffset_ : chatLogOffset_ -= 5;
    recalculateMessagePositions();
  }
}

void PlayerLogDisplay::finalize()
{
  // Do nothing for now.
}

std::string PlayerLogDisplay::splitStringWithNewlines( std::string& input )
{
  for ( int i = 0; i < static_cast< int >( input.size() ); i += charactersPerLine_ )
  {
    if ( i == 0 )
    {
      continue;
    }

    if ( static_cast< int >( input.size() ) > ( i + 1 ) )
    {
      if ( std::isalpha( input[ i + 1 ] ) )
      {
        int j = i;
        while ( j > 0 )
        {
          if ( std::isspace( input[ j ] ) )
          {
            break;
          }

          j--;
        }

        i = j;
      }
    }

    input.insert( i, "\n" );
  }

  return input;
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

    std::string textStr                = m->getString().toAnsiString();
    bool        stringContainsNewlines = std::find( std::begin( textStr ), std::end( textStr ), '\n' ) != textStr.end();

    if ( ! stringContainsNewlines )
    {
      textStr = splitStringWithNewlines( textStr );
      m->setString( textStr );
      m->setLineSpacing( 0.8f );
    }

    auto additionalNewLines = std::count_if( std::begin( textStr ), std::end( textStr ),
                                             []( char c )
                                             {
                                               return c == '\n';
                                             } );

    sf::Vector2f newPosition = startPosition - sf::Vector2f { 0.0f, static_cast< float >( ( i + additionalNewLines ) * FONT_SIZE ) };

    // Need to handle the case where each message could take up multiple lines
    m->setPosition( newPosition );
    i += static_cast< int >( additionalNewLines ) + 1;
  }
}

void PlayerLogDisplay::addMessage( sf::Text newMsg )
{
  std::string msgText = newMsg.getString().toAnsiString();
  if ( msgText.find( '\n' ) != msgText.npos )
  {
    msgText.erase( std::remove( std::begin( msgText ), std::end( msgText ), '\n' ) );
  }

  newMsg.setString( msgText );

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