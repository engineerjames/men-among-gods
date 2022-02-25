#include "NewButtonDisplay.h"

#include "PlayerData.h"
#include "UtilityFunctions.h"

#include <iostream>
#include <string>

namespace MenAmongGods
{
NewButtonDisplay::NewButtonDisplay( const sf::RenderWindow& window, PlayerData& playerData, const sf::Font& font, unsigned int fontSize,
                                    sf::Vector2f buttonSize )
    : window_( window )
    , playerData_( playerData )
    , buttonShape_( buttonSize )
    , buttonText_( "New", font, fontSize )
    , newCallback_()
{
  buttonText_.setFillColor( sf::Color::Black );
}

void NewButtonDisplay::setPosition( const sf::Vector2f& newPosition )
{
  buttonShape_.setPosition( newPosition );
  buttonText_.setPosition( sf::Vector2f { newPosition.x + 0.65f * buttonText_.getLocalBounds().width,
                                          newPosition.y + 0.33f * buttonShape_.getLocalBounds().height } );
}

void NewButtonDisplay::update()
{
}

void NewButtonDisplay::setCallBack( std::function< void() > callBack )
{
  newCallback_ = callBack;
}

void NewButtonDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    if ( buttonShape_.getGlobalBounds().contains( MenAmongGods::getNormalizedMousePosition( window_ ) ) )
    {
      playerData_.clear();
      newCallback_();
    }
  }
}

void NewButtonDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( buttonShape_, states );
  target.draw( buttonText_, states );
}

void NewButtonDisplay::finalize()
{
}

} // namespace MenAmongGods