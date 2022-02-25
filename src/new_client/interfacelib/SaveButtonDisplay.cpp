#include "SaveButtonDisplay.h"

#include "PlayerData.h"
#include "UtilityFunctions.h"

namespace MenAmongGods
{
SaveButtonDisplay::SaveButtonDisplay( const sf::RenderWindow& window, const PlayerData& playerData, const sf::Font& font,
                                      unsigned int fontSize, sf::Vector2f buttonSize )
    : window_( window )
    , playerData_( playerData )
    , buttonShape_( buttonSize )
    , buttonText_( "Save", font, fontSize )
{
  buttonText_.setFillColor( sf::Color::Black );
}

void SaveButtonDisplay::setPosition( const sf::Vector2f& newPosition )
{
  buttonShape_.setPosition( newPosition );
  buttonText_.setPosition( sf::Vector2f { newPosition.x + 0.50f * buttonText_.getLocalBounds().width,
                                          newPosition.y + 0.33f * buttonShape_.getLocalBounds().height } );
}

void SaveButtonDisplay::update()
{
}

void SaveButtonDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    if ( buttonShape_.getGlobalBounds().contains( MenAmongGods::getNormalizedMousePosition( window_ ) ) )
    {
      playerData_.saveToJsonFile( playerData_.getPlayerName() );
    }
  }
}

void SaveButtonDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( buttonShape_, states );
  target.draw( buttonText_, states );
}

void SaveButtonDisplay::finalize()
{
}

} // namespace MenAmongGods