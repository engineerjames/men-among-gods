
#include "RankDisplay.h"

#include "ColorPalette.h"
#include "GraphicsCache.h"
#include "PlayerData.h"
#include "UiConstants.h"
#include "RankNames.h"

namespace MenAmongGods
{
RankDisplay::RankDisplay( const sf::Font& font, PlayerData& playerData, GraphicsCache& gfxCache )
    : font_( font )
    , gfxCache_( gfxCache )
    , playerData_( playerData )
    , textualRank_( font, FONT_SIZE, "Private" )
    , rankSprite_()
{
  textualRank_.setJustification( MenAmongGods::JustifiableText::TextJustification::CENTER );
  textualRank_.setCenterWidth( 115 );
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
  if ( playerData_.getShowLook() )
  {
    textualRank_.setString( MenAmongGods::rankToString[ MenAmongGods::points2rank( playerData_.getLook().points ) ] );
    rankSprite_ = gfxCache_.getSprite( 10 + std::min( 20, MenAmongGods::points2rank( playerData_.getLook().points ) ) );
  }
  else
  {
    textualRank_.setString( playerData_.getRankString() );
    rankSprite_ = gfxCache_.getSprite( 10 + std::min( 20, playerData_.getRank() ) );
  }

  rankSprite_.setPosition( sf::Vector2f { 463, ( 54 - 16 ) } );
  textualRank_.update();
}

void RankDisplay::onUserInput( const sf::Event& )
{
  // Do nothing for now
}

void RankDisplay::finalize()
{
  // Do nothing for now
  textualRank_.finalize();
}

} // namespace MenAmongGods