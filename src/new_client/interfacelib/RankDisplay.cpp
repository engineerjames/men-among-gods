
#include "RankDisplay.h"

#include "ColorPalette.h"
#include "ConstantIdentifiers.h"
#include "GraphicsCache.h"
#include "PlayerData.h"
#include "UiPositions.h"

namespace MenAmongGods
{
RankDisplay::RankDisplay( const sf::Font& font, PlayerData& playerData, const GraphicsCache& gfxCache )
    : font_( font )
    , gfxCache_( gfxCache )
    , playerData_( playerData )
    , textualRank_( "Private", font, FONT_SIZE )
    , rankSprite_()
{
  textualRank_.setPosition( MenAmongGods::textualRankPosition );
  textualRank_.setFillColor( MenAmongGods::MsgYellow );
  textualRank_.setOutlineColor( sf::Color::Black );
}

void RankDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( textualRank_, states );
  target.draw( rankSprite_, states );
}

void RankDisplay::update()
{
  textualRank_.setString( playerData_.getRankString() );

  rankSprite_ = gfxCache_.getSprite( 10 + std::min( 20, playerData_.getRank() ) );
  rankSprite_.setPosition( sf::Vector2f { 463, ( 54 - 16 ) } );
}

void RankDisplay::onUserInput( const sf::Event& )
{
  // Do nothing for now
}

void RankDisplay::finalize()
{
  // Do nothing for now
}

} // namespace MenAmongGods