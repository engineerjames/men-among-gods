#include "PlayerShopDisplay.h"

#include <iostream>

#include "ClientTypes.h"
#include "ColorPalette.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "GuiFormatters.h"
#include "PlayerData.h"
#include "UiConstants.h"
#include "UtilityFunctions.h"

// Commands
#include "ShopCommand.h"

namespace MenAmongGods
{
PlayerShopDisplay::PlayerShopDisplay( const sf::RenderWindow& window, const sf::Font& font, PlayerData& pdata, GraphicsCache& gfxCache,
                                      const GraphicsIndex& gfxIndex )
    : MenAmongGods::Component()
    , window_( window )
    , playerData_( pdata )
    , gfxCache_( gfxCache )
    , gfxIndex_( gfxIndex )
    , priceCursor_()
{
  shopBackground_ = gfxCache_.getSprite( 92 );
  shopBackground_.setPosition( MenAmongGods::shopPosition );

  priceCursor_.setFont( font );
  priceCursor_.setCharacterSize( FONT_SIZE );
  priceCursor_.setOutlineColor( sf::Color::Black );
  priceCursor_.setOutlineThickness( 1.0f );
  priceCursor_.setFillColor( MenAmongGods::MsgYellow );
  priceCursor_.setString( "" );
}

void PlayerShopDisplay::update()
{
  if ( ! itemSprites_.empty() )
  {
    itemSprites_.clear();
  }
    
  if ( playerData_.getShouldShowShop() )
  {
    auto mousePosition = getNormalizedMousePosition( window_ );

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
           
      if ( newItem.getGlobalBounds().contains( mousePosition ) && shop.price[n] != 0)
      {
        priceCursor_.setString( MenAmongGods::goldToString( shop.price[ n ] ) );
        priceCursor_.setPosition( mousePosition + sf::Vector2f { 16.0f, 16.0f } );
      }

      itemSprites_.push_back( std::move( newItem ) );
    }

    if ( !shopBackground_.getGlobalBounds().contains( mousePosition ) )
    {
      priceCursor_.setString( "" );
    }
      
  }

  
}

void PlayerShopDisplay::onUserInput( const sf::Event& e )
{
  if ( ! playerData_.getShouldShowShop() )
  {
    return;
  }

  if ( e.type == sf::Event::TextEntered && sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Escape ) )
  {
    playerData_.setShouldShowShop( false );
  }

  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( closeShopButtonBoundingBox.contains( mousePosition ) )
    {
      playerData_.setShouldShowShop( false );
      return;
    }

    int tx = static_cast< int >( ( mousePosition.x - MenAmongGods::shopPosition.x ) / 35 );
    int ty = static_cast< int >( ( mousePosition.y - MenAmongGods::shopPosition.y ) / 35 );
    int nr = tx + ty * 8;

    look shop = playerData_.getShop();

    if ( shop.nr != 0 )
    {
      commands_.push_back( std::make_shared< MenAmongGods::ShopCommand >( shop.nr, nr ) );
    }
  }
}

void PlayerShopDisplay::finalize()
{
}

void PlayerShopDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  if ( ! playerData_.getShouldShowShop() )
  {
    return;
  }

  target.draw( shopBackground_, states );
  
  for ( const auto& i : itemSprites_ )
  {
    target.draw( i, states );
  }

  target.draw( priceCursor_, states );
}

} // namespace MenAmongGods