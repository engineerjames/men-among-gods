#include "PlayerShopDisplay.h"

#include <iostream>

#include "ClientTypes.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "PlayerData.h"
#include "UiPositions.h"

namespace MenAmongGods
{
PlayerShopDisplay::PlayerShopDisplay( const sf::RenderWindow& window, const PlayerData& pdata, const GraphicsCache& gfxCache,
                                      const GraphicsIndex& gfxIndex )
    : MenAmongGods::Component()
    , window_( window )
    , playerData_( pdata )
    , gfxCache_( gfxCache )
    , gfxIndex_( gfxIndex )
{
  shopBackground_ = gfxCache_.getSprite( 92 );
  shopBackground_.setPosition( MenAmongGods::shopPosition );
}

void PlayerShopDisplay::update()
{
  itemSprites_.clear();

  if ( playerData_.getShouldShowShop() )
  {
    look shop = playerData_.getShop();

    for ( int n = 0; n < 62; ++n )
    {
      if ( shop.item[ n ] == 0 )
      {
        continue;
      }

      sf::Sprite   newItem = gfxCache_.getSprite( shop.item[ n ] );
      sf::Vector2f newItemPosition { static_cast< float >( 222 + ( n % 8 ) * 35 ), static_cast< float >( 262 + ( n / 8 ) * 35 ) };

      newItem.setPosition( newItemPosition );
    }
  }
}

void PlayerShopDisplay::onUserInput( const sf::Event& )
{
}

void PlayerShopDisplay::finalize()
{
}

void PlayerShopDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( shopBackground_, states );
}

} // namespace MenAmongGods