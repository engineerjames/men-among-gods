#include "UserOptionPanelDisplay.h"

#include "ColorPalette.h"
#include "PlayerData.h"
#include "UiPositions.h"
#include "UtilityFunctions.h"

namespace MenAmongGods
{
UserOptionPanelDisplay::UserOptionPanelDisplay( const sf::RenderWindow& window, PlayerData& playerData )
    : MenAmongGods::Component()
    , window_( window )
    , playerData_( playerData )
    , fastModeRectangle_()
    , normModeRectangle_()
    , slowModeRectangle_()
    , hideWallsRectangle_()
    , hideNamesRectangle_()
    , hideHealthRectangle_()
    , rectangles_()
{

  // TODO: should we have a clickable rectangle class? Perhaps...
  rectangles_ = { &fastModeRectangle_,  &normModeRectangle_,  &slowModeRectangle_,
                  &hideWallsRectangle_, &hideNamesRectangle_, &hideHealthRectangle_ };

  for ( const auto& r : rectangles_ )
  {
    r->setOutlineColor( MenAmongGods::SelectionOrange );
    r->setOutlineThickness( 1.0f );
    r->setFillColor( sf::Color { 255, 255, 255, 0 } );
    r->setSize( MenAmongGods::CLIENT_SELECTION_BOX_SIZE );
  }
  fastModeRectangle_.setPosition( MenAmongGods::clientOptionsOrigin );
  normModeRectangle_.setPosition( MenAmongGods::clientOptionsOrigin + sf::Vector2f { MenAmongGods::CLIENT_SELECTION_SPACING_X, 0.0f } );
  slowModeRectangle_.setPosition( MenAmongGods::clientOptionsOrigin +
                                  sf::Vector2f { 2.0f * MenAmongGods::CLIENT_SELECTION_SPACING_X, 0.0f } );
}

void UserOptionPanelDisplay::update()
{
}

void UserOptionPanelDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  // We only want to draw what is currently active for the hide options, but we always draw a mode
  switch ( playerData_.getMode() )
  {
  case 0:
    target.draw( slowModeRectangle_, states );
    break;
  case 1:
    target.draw( normModeRectangle_, states );
    break;
  case 2:
    target.draw( fastModeRectangle_, states );
    break;

  default:
    std::cerr << "Invalid mode in draw() for UserOptionPanelDisplay" << std::endl;
    target.draw( normModeRectangle_, states );
    break;
  }
}

void UserOptionPanelDisplay::onUserInput( const sf::Event& e )
{
  // TODO: update this design to use an enum instead of these sentinel values
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );

    if ( slowModeRectangle_.getGlobalBounds().contains( mousePosition ) )
    {
      playerData_.setMode( 0 );
    }
    else if ( normModeRectangle_.getGlobalBounds().contains( mousePosition ) )
    {
      playerData_.setMode( 1 );
    }
    else if ( fastModeRectangle_.getGlobalBounds().contains( mousePosition ) )
    {
      playerData_.setMode( 2 );
    }
  }
}

void UserOptionPanelDisplay::finalize()
{
}

} // namespace MenAmongGods