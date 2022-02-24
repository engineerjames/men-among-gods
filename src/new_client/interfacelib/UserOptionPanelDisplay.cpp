#include "UserOptionPanelDisplay.h"

#include "ColorPalette.h"
#include "PlayerData.h"
#include "UiPositions.h"
#include "UtilityFunctions.h"

// Commands
#include "ExitCommand.h"
#include "ModeCommand.h"

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
    , exitRectangle_()
    , rectangles_()
{

  // TODO: should we have a clickable rectangle class? Perhaps...
  rectangles_ = { &fastModeRectangle_,  &normModeRectangle_,   &slowModeRectangle_, &hideWallsRectangle_,
                  &hideNamesRectangle_, &hideHealthRectangle_, &exitRectangle_ };

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

  hideHealthRectangle_.setPosition( MenAmongGods::clientOptionsOrigin +
                                    sf::Vector2f { 3.0f * MenAmongGods::CLIENT_SELECTION_SPACING_X, 0.0f } );

  hideNamesRectangle_.setPosition( MenAmongGods::clientOptionsOrigin + sf::Vector2f { 2.0f * MenAmongGods::CLIENT_SELECTION_SPACING_X,
                                                                                      MenAmongGods::CLIENT_SELECTION_SPACING_Y } );

  hideWallsRectangle_.setPosition( MenAmongGods::clientOptionsOrigin + sf::Vector2f { 1.0f * MenAmongGods::CLIENT_SELECTION_SPACING_X,
                                                                                      MenAmongGods::CLIENT_SELECTION_SPACING_Y } );

  exitRectangle_.setPosition( MenAmongGods::clientOptionsOrigin + sf::Vector2f { 3.0f * MenAmongGods::CLIENT_SELECTION_SPACING_X,
                                                                                 +2.0f * MenAmongGods::CLIENT_SELECTION_SPACING_Y } );
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
    LOG_ERROR( "Invalid mode in draw()" );
    target.draw( normModeRectangle_, states );
    break;
  }

  if ( playerData_.clientShouldShowPercentHealth() )
  {
    target.draw( hideHealthRectangle_, states );
  }

  if ( playerData_.clientShouldShowNames() )
  {
    target.draw( hideNamesRectangle_, states );
  }

  if ( playerData_.areWallsHidden() != 0 ) // TODO: Update areWallsHidden() to return a bool
  {
    target.draw( hideWallsRectangle_, states );
  }
}

void UserOptionPanelDisplay::onUserInput( const sf::Event& e )
{
  // TODO: update this design to use an enum instead of these sentinel values
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );

    // Slow/Normal/Fast modes
    if ( slowModeRectangle_.getGlobalBounds().contains( mousePosition ) )
    {
      int slowMode = 0;
      playerData_.setMode( slowMode );
      commands_.push_back( std::make_shared< MenAmongGods::ModeCommand >( slowMode ) );
    }
    else if ( normModeRectangle_.getGlobalBounds().contains( mousePosition ) )
    {
      int normMode = 1;
      playerData_.setMode( normMode );
      commands_.push_back( std::make_shared< MenAmongGods::ModeCommand >( normMode ) );
    }
    else if ( fastModeRectangle_.getGlobalBounds().contains( mousePosition ) )
    {
      int fastMode = 2;
      playerData_.setMode( fastMode );
      commands_.push_back( std::make_shared< MenAmongGods::ModeCommand >( fastMode ) );
    }

    // Exit
    if ( exitRectangle_.getGlobalBounds().contains( mousePosition ) )
    {
      commands_.push_back( std::make_shared< MenAmongGods::ExitCommand >() );
    }

    // Hide walls - true->false, false->true when clicked
    if ( hideWallsRectangle_.getGlobalBounds().contains( mousePosition ) )
    {
      if ( playerData_.areWallsHidden() != 0 )
      {
        playerData_.setClientShouldHideWalls( false );
      }
      else
      {
        playerData_.setClientShouldHideWalls( true );
      }
    }

    // Hide health - true->false, false->true when clicked
    if ( hideHealthRectangle_.getGlobalBounds().contains( mousePosition ) )
    {
      playerData_.setClientShouldShowPercentHealth( ! playerData_.clientShouldShowPercentHealth() );
    }

    // Hide names - true->false, false->true when clicked
    if ( hideNamesRectangle_.getGlobalBounds().contains( mousePosition ) )
    {
      playerData_.setClientShouldShowNames( ! playerData_.clientShouldShowNames() );
    }
  }
}

void UserOptionPanelDisplay::finalize()
{
}

} // namespace MenAmongGods