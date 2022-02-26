#include "PlayerInventoryDisplay.h"

#include "ColorPalette.h"
#include "ConstantIdentifiers.h"
#include "GraphicsCache.h"
#include "PlayerData.h"
#include "UiPositions.h"
#include "UtilityFunctions.h"

#include <cmath>
#include <iostream>

// Commands
#include "InventoryCommand.h"
#include "InventoryLookCommand.h"

namespace MenAmongGods
{

PlayerInventoryDisplay::PlayerInventoryDisplay( const sf::RenderWindow& window, const PlayerData& playerData,
                                                const GraphicsCache& gfxCache )
    : window_( window )
    , playerData_( playerData )
    , gfxCache_( gfxCache )
    , equipmentSprites_()
    , scrollBar_()
    , upArrow_( MenAmongGods::inventoryScrollUpBoxPosition, MenAmongGods::scrollBoxSize )
    , downArrow_( MenAmongGods::inventoryScrollDownBoxPosition, MenAmongGods::scrollBoxSize )
    , scrollPosition_( 0 )
{
  scrollBar_.setPosition( MenAmongGods::inventoryScrollBarPosition );
  scrollBar_.setSize( MenAmongGods::inventoryScrollBarSize );
  scrollBar_.setFillColor( MenAmongGods::ScrollBarGreen );
}

void PlayerInventoryDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( const auto& s : equipmentSprites_ )
  {
    target.draw( s, states );
  }

  target.draw( scrollBar_, states );
}

void PlayerInventoryDisplay::update()
{
  equipmentSprites_.clear();
  int drawnItems = 0;
  for ( unsigned int i = scrollPosition_ * 2; i < N_ITEMS; ++i )
  {
    int        pitem      = playerData_.getItem( i );
    sf::Sprite itemSprite = gfxCache_.getSprite( pitem );

    equipmentSprites_.push_back( itemSprite );
    auto& lastSprite = *( equipmentSprites_.end() - 1 );

    sf::Vector2f spritePosition { static_cast< float >( 220 + ( drawnItems % 2 ) * 35 ),
                                  static_cast< float >( 2 + ( drawnItems / 2 ) * 35 ) };
    lastSprite.setPosition( spritePosition );

    // Only 10 items can be displayed at once
    drawnItems++;
    if ( drawnItems == 10 )
    {
      break;
    }
  }

  // Set scroll bar position
  scrollBar_.setPosition( MenAmongGods::inventoryScrollBarPosition +
                          MenAmongGods::scrollBarMovementPerClick * static_cast< float >( scrollPosition_ ) );

  int carriedItem = playerData_.getCarriedItem();
  if ( carriedItem != 0 )
  {
    sf::Sprite carriedItemSprite = gfxCache_.getSprite( carriedItem );
    carriedItemSprite.setPosition( getNormalizedMousePosition( window_ ) );
    equipmentSprites_.push_back( carriedItemSprite );
  }
}

void PlayerInventoryDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );

    if ( upArrow_.contains( mousePosition ) )
    {
      scrollPosition_ = std::max( scrollPosition_ - 1, 0 );
    }
    else if ( downArrow_.contains( mousePosition ) )
    {
      scrollPosition_ = std::min( scrollPosition_ + 1, 15 );
    }
    else if ( MenAmongGods::inventoryBoundingBox.contains( mousePosition ) )
    {
      // If you draw out the positions involved the math makes more sense, but essentially it breaks
      // down into these steps:
      // 1. Offset the mouse position by the starting position of the inventory "bounding box"--that
      //    way we can continue the math assuming our mouse position is relative to the upper left
      //    corner of the inventory bounding box.
      //
      // 2. Since there are 5 rows, divide the height of the bounding box into 5 'slices', and see
      //    how many times our mouse position offset (in Y) would fit into it.  We use the floor
      //    of the value, since 3.5, 3.6, etc., we still want to associate with row 3 (otherwise, the
      //    user clicking over halfway through box N would end up activating item in N + 1).
      int itemRow = static_cast< int >( std::floor( ( mousePosition.y - MenAmongGods::inventoryBoundingBoxPosition.y ) /
                                                    ( MenAmongGods::inventoryBoundingBox.height / 5.0f ) ) );

      // We'll do a similar strategy for the columns, except there are only two columns in this case
      int itemColumn = static_cast< int >( std::floor( ( mousePosition.x - MenAmongGods::inventoryBoundingBoxPosition.x ) /
                                                       ( MenAmongGods::inventoryBoundingBox.width / 2.0f ) ) );

      int itemPosition = ( 2 * scrollPosition_ ) + ( 2 * itemRow ) + itemColumn;

      if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LShift ) )
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 0u, itemPosition, 0 ) );
      }
      else
      {
        // TODO: For now, always send the command to the server, even if it won't ultimately do anything
        //       but we should probably evaluate if we _should_ do this.
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 6u, itemPosition, 0 ) );
      }
    }
  }

  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Right )
  {
    sf::Vector2f mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );

    // TODO: Clean up this duplicate code
    int itemRow = static_cast< int >( std::floor( ( mousePosition.y - MenAmongGods::inventoryBoundingBoxPosition.y ) /
                                                  ( MenAmongGods::inventoryBoundingBox.height / 5.0f ) ) );

    // We'll do a similar strategy for the columns, except there are only two columns in this case
    int itemColumn = static_cast< int >( std::floor( ( mousePosition.x - MenAmongGods::inventoryBoundingBoxPosition.x ) /
                                                     ( MenAmongGods::inventoryBoundingBox.width / 2.0f ) ) );

    int itemPosition = ( 2 * scrollPosition_ ) + ( 2 * itemRow ) + itemColumn;

    // WHY do we pass in the selected_char when looking at an item? It doesn't seem to do anything..
    commands_.push_back( std::make_shared< MenAmongGods::InventoryLookCommand >( itemPosition, 0 ) );
  }
}

void PlayerInventoryDisplay::finalize()
{
}

} // namespace MenAmongGods