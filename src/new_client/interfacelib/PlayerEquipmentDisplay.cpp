#include "PlayerEquipmentDisplay.h"

#include "ConstantIdentifiers.h"
#include "GraphicsCache.h"
#include "PlayerData.h"
#include "UiPositions.h"
#include "UtilityFunctions.h"

#include <cmath>
#include <iostream>

// Commands
#include "InventoryCommand.h"

namespace
{
static int wntab[ 20 ] = { WN_HEAD, WN_CLOAK, WN_BODY, WN_ARMS, WN_NECK, WN_BELT, WN_RHAND, WN_LHAND, WN_RRING, WN_LRING,
                           WN_LEGS, WN_FEET,  0,       0,       0,       0,       0,        0,        0,        0 };
}

namespace MenAmongGods
{

PlayerEquipmentDisplay::PlayerEquipmentDisplay( const sf::RenderWindow& window, const PlayerData& playerData, GraphicsCache& gfxCache )
    : window_( window )
    , playerData_( playerData )
    , gfxCache_( gfxCache )
    , inventorySprites_()
{
}

void PlayerEquipmentDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( const auto& s : inventorySprites_ )
  {
    target.draw( s, states );
  }
}

void PlayerEquipmentDisplay::update()
{
  inventorySprites_.clear();

  for ( unsigned int n = 0; n < 12; n++ )
  {
    const int& itemReference = playerData_.getClientSidePlayerInfo().worn[ wntab[ n ] ];

    if ( itemReference != 0 )
    {
      sf::Sprite newSprite = gfxCache_.getSprite( itemReference );
      newSprite.setPosition( sf::Vector2f { static_cast< float >( 303 + ( n % 2 ) * 35 ), static_cast< float >( 2 + ( n / 2 ) * 35 ) } );
      inventorySprites_.push_back( newSprite );
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
  }
}

void PlayerEquipmentDisplay::finalize()
{
}

} // namespace MenAmongGods