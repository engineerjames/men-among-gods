#include "PlayerInventoryDisplay.h"

#include "ColorPalette.h"
#include "ConstantIdentifiers.h"
#include "GraphicsCache.h"
#include "PlayerData.h"
#include "UiPositions.h"
#include "UtilityFunctions.h"

#include <iostream>

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
  for ( unsigned int i = scrollPosition_ * 2; i < N_ITEMS; ++i )
  {
    int        pitem      = playerData_.getItem( i );
    sf::Sprite itemSprite = gfxCache_.getSprite( pitem );

    equipmentSprites_.push_back( itemSprite );
    auto& lastSprite = *( equipmentSprites_.end() - 1 );

    sf::Vector2f spritePosition { static_cast< float >( 220 + ( i % 2 ) * 35 ), static_cast< float >( 2 + ( i / 2 ) * 35 ) };
    lastSprite.setPosition( spritePosition );
    // Only 10 items can be displayed at once
    if ( i == 10 )
    {
      break;
    }
  }
}

void PlayerInventoryDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = MenAmongGods::getNormalizedMousePosition( window_ );

    if ( upArrow_.contains( mousePosition ) )
    {
      std::cerr << "UP CLICK" << std::endl;
      scrollPosition_ = std::max( scrollPosition_ - 1, 0 );

      std::cerr << scrollPosition_ << std::endl;
    }
    else if ( downArrow_.contains( mousePosition ) )
    {
      std::cerr << "DOWN CLICK" << std::endl;
      scrollPosition_ = std::min( scrollPosition_ + 1, 15 );

      std::cerr << scrollPosition_ << std::endl;
    }
  }
}

void PlayerInventoryDisplay::finalize()
{
}

} // namespace MenAmongGods