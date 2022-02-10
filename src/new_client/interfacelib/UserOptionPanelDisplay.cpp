#include "UserOptionPanelDisplay.h"

#include "ColorPalette.h"
#include "PlayerData.h"
#include "UiPositions.h"

namespace MenAmongGods
{
UserOptionPanelDisplay::UserOptionPanelDisplay( PlayerData& playerData )
    : MenAmongGods::Component()
    , playerData_( playerData )
    , modeRectangle_()
    , hideWallsRectangle_()
    , hideNamesRectangle_()
    , hideHealthRectangle_()
    , rectangles_()
{

  // TODO: should we have a clickable rectangle class? Perhaps...
  rectangles_ = { &modeRectangle_, &hideWallsRectangle_, &hideNamesRectangle_, &hideHealthRectangle_ };

  for ( const auto& r : rectangles_ )
  {
    r->setOutlineColor( MenAmongGods::SelectionOrange );
    r->setOutlineThickness( 1.0f );
  }
}

void UserOptionPanelDisplay::update()
{
  int playerMode = playerData_.getMode();
  if ( playerMode == 0 ) // Slow
  {
    modeRectangle_.setPosition( MenAmongGods::clientOptionsOrigin +
                                sf::Vector2f { 2.0f * MenAmongGods::CLIENT_SELECTION_SPACING_X, 0.0f } );
  }
  else if ( playerMode == 1 ) // Normal
  {
    modeRectangle_.setPosition( MenAmongGods::clientOptionsOrigin + sf::Vector2f { MenAmongGods::CLIENT_SELECTION_SPACING_X, 0.0f } );
  }
  else // Fast
  {
    modeRectangle_.setPosition( MenAmongGods::clientOptionsOrigin );
  }
}

void UserOptionPanelDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  // We only want to draw what is currently active for the hide options, but we always draw a mode
  target.draw( modeRectangle_, states );
}

void UserOptionPanelDisplay::onUserInput( const sf::Event& )
{
}

void UserOptionPanelDisplay::finalize()
{
}

} // namespace MenAmongGods