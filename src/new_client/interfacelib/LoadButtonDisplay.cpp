#include "LoadButtonDisplay.h"

#include "PlayerData.h"
#include "ResourceLocations.h"
#include "UtilityFunctions.h"

#include <iostream>
#include <string>

namespace MenAmongGods
{
LoadButtonDisplay::LoadButtonDisplay( const sf::RenderWindow& window, PlayerData& playerData, const sf::Font& font, unsigned int fontSize,
                                      sf::Vector2f buttonSize )
    : window_( window )
    , playerData_( playerData )
    , buttonShape_( buttonSize )
    , buttonText_( "Load", font, fontSize )
    , paths_()
    , fileList_()
{
  buttonText_.setFillColor( sf::Color::Black );
}

void LoadButtonDisplay::setPosition( const sf::Vector2f& newPosition )
{
  buttonShape_.setPosition( newPosition );
  buttonText_.setPosition( sf::Vector2f { newPosition.x + 0.50f * buttonText_.getLocalBounds().width,
                                          newPosition.y + 0.33f * buttonShape_.getLocalBounds().height } );
}

void LoadButtonDisplay::update()
{
  fileList_.clear();

  sf::Vector2f startingPosition = buttonShape_.getPosition();
  float        multiplier       = 1.0f;
  for ( const auto& p : paths_ )
  {
    fileList_.emplace_back( p.filename().string(), *buttonText_.getFont(), 10 );

    sf::Text& last = *( std::end( fileList_ ) - 1 );

    last.setPosition( startingPosition + sf::Vector2f { 0.0f, buttonShape_.getLocalBounds().height + multiplier * 15.0f } );
    multiplier += 1.0f;
  }
}

void LoadButtonDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    if ( buttonShape_.getGlobalBounds().contains( MenAmongGods::getNormalizedMousePosition( window_ ) ) )
    {
      paths_.clear();

      for ( auto const& file : std::filesystem::directory_iterator { MenAmongGods::getConfigPath() } )
      {
        if ( file.is_regular_file() && file.path().has_extension() && file.path().extension().string() == ".moa" )
        {
          paths_.push_back( file );
        }
      }
    }

    for ( const auto& f : fileList_ )
    {
      if ( f.getGlobalBounds().contains( MenAmongGods::getNormalizedMousePosition( window_ ) ) )
      {
        std::cerr << "Clicked on " << f.getString().toAnsiString() << std::endl;
        paths_.clear();
        playerData_.loadFromJsonFile( f.getString().toAnsiString() );
      }
    }
  }
}

void LoadButtonDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( buttonShape_, states );
  target.draw( buttonText_, states );

  for ( const auto& text : fileList_ )
  {
    target.draw( text, states );
  }
}

void LoadButtonDisplay::finalize()
{
}

} // namespace MenAmongGods