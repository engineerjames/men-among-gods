#include "PlayerEquipmentDisplay.h"

#include "GraphicsCache.h"
#include "PlayerData.h"
#include "UiConstants.h"
#include "UtilityFunctions.h"

#include <cmath>
#include <iostream>

#include "EquipmentConstants.h"

// Commands
#include "InventoryCommand.h"

namespace
{
static int wntab[ 20 ] = { static_cast< int >( WEAR_POSITIONS::WN_HEAD ),
                           static_cast< int >( WEAR_POSITIONS::WN_CLOAK ),
                           static_cast< int >( WEAR_POSITIONS::WN_BODY ),
                           static_cast< int >( WEAR_POSITIONS::WN_ARMS ),
                           static_cast< int >( WEAR_POSITIONS::WN_NECK ),
                           static_cast< int >( WEAR_POSITIONS::WN_BELT ),
                           static_cast< int >( WEAR_POSITIONS::WN_RHAND ),
                           static_cast< int >( WEAR_POSITIONS::WN_LHAND ),
                           static_cast< int >( WEAR_POSITIONS::WN_RRING ),
                           static_cast< int >( WEAR_POSITIONS::WN_LRING ),
                           static_cast< int >( WEAR_POSITIONS::WN_LEGS ),
                           static_cast< int >( WEAR_POSITIONS::WN_FEET ),
                           0,
                           0,
                           0,
                           0,
                           0,
                           0,
                           0,
                           0 };
}

namespace MenAmongGods
{

PlayerEquipmentDisplay::PlayerEquipmentDisplay( const sf::RenderWindow& window, PlayerData& playerData, GraphicsCache& gfxCache )
    : window_( window )
    , playerData_( playerData )
    , gfxCache_( gfxCache )
    , equipmentSprites_()
    , highlightedSprite_( )
{
}

void PlayerEquipmentDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( const auto& s : equipmentSprites_ )
  {
    target.draw( s, states );
  }

  if ( highlightedSprite_.has_value() )
  {
    sf::RenderStates additiveState {};
    additiveState.blendMode = sf::BlendAdd;

    target.draw( *highlightedSprite_, additiveState );
  }
}

void PlayerEquipmentDisplay::update()
{
  equipmentSprites_.clear();
  highlightedSprite_.reset();

  if ( playerData_.getShowLook() )
  { // TODO: Simplify this logic
    for ( unsigned int n = 0; n < 12; n++ )
    {
      const int& itemReference = playerData_.getLook().worn[ wntab[ n ] ];

      if ( itemReference != 0 )
      {
        sf::Sprite newSprite = gfxCache_.getSprite( itemReference );
        newSprite.setPosition( sf::Vector2f { static_cast< float >( 303 + ( n % 2 ) * 35 ), static_cast< float >( 2 + ( n / 2 ) * 35 ) } );
        equipmentSprites_.push_back( newSprite );
      }
    }
  }
  else
  {
    for ( unsigned int n = 0; n < 12; n++ )
    {
      const int& itemReference = playerData_.getClientSidePlayerInfo().worn[ wntab[ n ] ];

      if ( itemReference != 0 )
      {
        sf::Sprite newSprite = gfxCache_.getSprite( itemReference );

        const float        xPosition = static_cast< float >( 303 + ( n % 2 ) * 35 );
        const float        yPosition = static_cast< float >( 2 + ( n / 2 ) * 35 );
        const sf::Vector2f upperLeftCorner { xPosition, yPosition };

        newSprite.setPosition( upperLeftCorner );
        equipmentSprites_.push_back( newSprite );

        sf::FloatRect itemBox { upperLeftCorner, sf::Vector2f { 32.0f, 32.0f } };
        if ( itemBox.contains( MenAmongGods::getNormalizedMousePosition( window_ ) ) )
        {
          highlightedSprite_ = newSprite;
        }
      }
    }
  }

  // Set Hover states - TODO: Combine PlayerEquipment and PlayerInventory
  sf::Vector2f mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );
  int          carriedItem   = playerData_.getCarriedItem();

  if ( MenAmongGods::equipmentBoundingBox.contains( mousePosition ) )
  {
    if ( carriedItem == 0 )
    {
      if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LShift ) )
      {
        playerData_.setHoverState( PlayerData::HoverState::PICKUP );
      }
      else
      {
        playerData_.setHoverState( PlayerData::HoverState::USE );
      }
    }
    else if ( carriedItem != 0 )
    {
      if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LShift ) )
      {
        playerData_.setHoverState( PlayerData::HoverState::DROP );
      }
      else
      {
        playerData_.setHoverState( PlayerData::HoverState::USE );
      }
    }
  }
}

void PlayerEquipmentDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left &&
       sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LShift ) )
  {
    sf::Vector2f mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );

    if ( MenAmongGods::equipmentBoundingBox.contains( mousePosition ) )
    {
      int itemRow = static_cast< int >( std::floor( ( mousePosition.y - MenAmongGods::equipmentBoundingBoxPosition.y ) /
                                                    ( MenAmongGods::equipmentBoundingBox.height / 6.0f ) ) );

      // We'll do a similar strategy for the columns, except there are only two columns in this case
      int itemColumn = static_cast< int >( std::floor( ( mousePosition.x - MenAmongGods::equipmentBoundingBoxPosition.x ) /
                                                       ( MenAmongGods::equipmentBoundingBox.width / 2.0f ) ) );

      // TODO: The last parameter should be the selected character--though
      // not sure why that would matter for equipping things...
      if ( itemRow == 0 && itemColumn == 0 ) // head
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 0u, 0u ) );
      }
      else if ( itemRow == 0 && itemColumn == 1 ) // back
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 9u, 0u ) );
      }
      else if ( itemRow == 1 && itemColumn == 0 ) // chest
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 2u, 0u ) );
      }
      else if ( itemRow == 1 && itemColumn == 1 ) // arms
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 3u, 0u ) );
      }
      else if ( itemRow == 2 && itemColumn == 0 ) // neck
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 1u, 0u ) );
      }
      else if ( itemRow == 2 && itemColumn == 1 ) // belt
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 4u, 0u ) );
      }
      else if ( itemRow == 3 && itemColumn == 0 ) // right hand
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 8u, 0u ) );
      }
      else if ( itemRow == 3 && itemColumn == 1 ) // left hand
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 7u, 0u ) );
      }
      else if ( itemRow == 4 && itemColumn == 1 ) // right ring
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 10u, 0u ) );
      }
      else if ( itemRow == 4 && itemColumn == 0 ) // left ring
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 11u, 0u ) );
      }
      else if ( itemRow == 5 && itemColumn == 0 ) // legs
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 5u, 0u ) );
      }
      else if ( itemRow == 5 && itemColumn == 1 ) // boots
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 1u, 6u, 0u ) );
      }
    }

    return;
  }

  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Right )
  {
    sf::Vector2f mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );

    if ( MenAmongGods::equipmentBoundingBox.contains( mousePosition ) )
    {
      int itemRow = static_cast< int >( std::floor( ( mousePosition.y - MenAmongGods::equipmentBoundingBoxPosition.y ) /
                                                    ( MenAmongGods::equipmentBoundingBox.height / 6.0f ) ) );

      // We'll do a similar strategy for the columns, except there are only two columns in this case
      int itemColumn = static_cast< int >( std::floor( ( mousePosition.x - MenAmongGods::equipmentBoundingBoxPosition.x ) /
                                                       ( MenAmongGods::equipmentBoundingBox.width / 2.0f ) ) );

      // TODO: The last parameter should be the selected character--though
      // not sure why that would matter for equipping things...
      if ( itemRow == 0 && itemColumn == 0 ) // head
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 0u, 0u ) );
      }
      else if ( itemRow == 0 && itemColumn == 1 ) // back
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 9u, 0u ) );
      }
      else if ( itemRow == 1 && itemColumn == 0 ) // chest
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 2u, 0u ) );
      }
      else if ( itemRow == 1 && itemColumn == 1 ) // arms
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 3u, 0u ) );
      }
      else if ( itemRow == 2 && itemColumn == 0 ) // neck
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 1u, 0u ) );
      }
      else if ( itemRow == 2 && itemColumn == 1 ) // belt
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 4u, 0u ) );
      }
      else if ( itemRow == 3 && itemColumn == 0 ) // right hand
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 8u, 0u ) );
      }
      else if ( itemRow == 3 && itemColumn == 1 ) // left hand
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 7u, 0u ) );
      }
      else if ( itemRow == 4 && itemColumn == 0 ) // right ring
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 10u, 0u ) );
      }
      else if ( itemRow == 4 && itemColumn == 1 ) // left ring
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 11u, 0u ) );
      }
      else if ( itemRow == 5 && itemColumn == 0 ) // legs
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 5u, 0u ) );
      }
      else if ( itemRow == 5 && itemColumn == 1 ) // boots
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 7u, 6u, 0u ) );
      }
    }

    return;
  }

  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );

    if ( MenAmongGods::equipmentBoundingBox.contains( mousePosition ) )
    {
      int itemRow = static_cast< int >( std::floor( ( mousePosition.y - MenAmongGods::equipmentBoundingBoxPosition.y ) /
                                                    ( MenAmongGods::equipmentBoundingBox.height / 6.0f ) ) );

      // We'll do a similar strategy for the columns, except there are only two columns in this case
      int itemColumn = static_cast< int >( std::floor( ( mousePosition.x - MenAmongGods::equipmentBoundingBoxPosition.x ) /
                                                       ( MenAmongGods::equipmentBoundingBox.width / 2.0f ) ) );

      if ( itemRow == 0 && itemColumn == 0 ) // head
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 0u, 0u ) );
      }
      else if ( itemRow == 0 && itemColumn == 1 ) // back
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 9u, 0u ) );
      }
      else if ( itemRow == 1 && itemColumn == 0 ) // chest
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 2u, 0u ) );
      }
      else if ( itemRow == 1 && itemColumn == 1 ) // arms
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 3u, 0u ) );
      }
      else if ( itemRow == 2 && itemColumn == 0 ) // neck
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 1u, 0u ) );
      }
      else if ( itemRow == 2 && itemColumn == 1 ) // belt
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 4u, 0u ) );
      }
      else if ( itemRow == 3 && itemColumn == 0 ) // right hand
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 8u, 0u ) );
      }
      else if ( itemRow == 3 && itemColumn == 1 ) // left hand
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 7u, 0u ) );
      }
      else if ( itemRow == 4 && itemColumn == 0 ) // right ring
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 11u, 0u ) );
      }
      else if ( itemRow == 4 && itemColumn == 1 ) // left ring
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 10u, 0u ) );
      }
      else if ( itemRow == 5 && itemColumn == 0 ) // legs
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 5u, 0u ) );
      }
      else if ( itemRow == 5 && itemColumn == 1 ) // boots
      {
        commands_.push_back( std::make_shared< MenAmongGods::InventoryCommand >( 5u, 6u, 0u ) );
      }
    }

    return;
  }
}

void PlayerEquipmentDisplay::finalize()
{
}

} // namespace MenAmongGods