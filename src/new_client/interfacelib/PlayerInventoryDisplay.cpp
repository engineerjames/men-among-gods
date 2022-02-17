#include "PlayerInventoryDisplay.h"

#include "ConstantIdentifiers.h"
#include "GraphicsCache.h"
#include "PlayerData.h"

namespace MenAmongGods
{

PlayerInventoryDisplay::PlayerInventoryDisplay( const PlayerData& playerData, const GraphicsCache& gfxCache )
    : playerData_( playerData )
    , gfxCache_( gfxCache )
    , equipmentSprites_()
{
}

void PlayerInventoryDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( const auto& s : equipmentSprites_ )
  {
    target.draw( s, states );
  }
}

void PlayerInventoryDisplay::update()
{
  equipmentSprites_.clear();
  for ( unsigned int i = 0; i < N_ITEMS; ++i )
  {
    playerData_.getItem( i );
  }
  // copyspritex(pl.item[n+inv_pos],220+(n%2)*35,2+(n/2)*35,0);
}

void PlayerInventoryDisplay::onUserInput( const sf::Event& )
{
}

void PlayerInventoryDisplay::finalize()
{
}

} // namespace MenAmongGods