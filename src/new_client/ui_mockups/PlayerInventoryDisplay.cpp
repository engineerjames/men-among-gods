#include "PlayerInventoryDisplay.h"

#include "../ConstantIdentifiers.h"
#include "../PlayerData.h"
#include "GraphicsCache.h"

namespace
{
static int wntab[ 20 ] = { WN_HEAD, WN_CLOAK, WN_BODY, WN_ARMS, WN_NECK, WN_BELT, WN_RHAND, WN_LHAND, WN_RRING, WN_LRING,
                           WN_LEGS, WN_FEET,  0,       0,       0,       0,       0,        0,        0,        0 };
}

namespace MenAmongGods
{

PlayerInventoryDisplay::PlayerInventoryDisplay( const PlayerData& playerData, const GraphicsCache& gfxCache )
    : playerData_( playerData )
    , gfxCache_( gfxCache )
    , inventorySprites_()
{
}

void PlayerInventoryDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( const auto& s : inventorySprites_ )
  {
    target.draw( s, states );
  }
}

void PlayerInventoryDisplay::update()
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

void PlayerInventoryDisplay::onUserInput( const sf::Event& )
{
}

void PlayerInventoryDisplay::finalize()
{
}

} // namespace MenAmongGods