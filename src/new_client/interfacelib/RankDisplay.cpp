
#include "RankDisplay.h"

#include "ColorPalette.h"
#include "ConstantIdentifiers.h"
#include "GraphicsCache.h"
#include "PlayerData.h"
#include "UiPositions.h"
#include "RankNames.h"

// TODO: Reduce this duplication
namespace
{
int points2rank( int v )
{
  if ( v < 50 )
    return 0;
  if ( v < 850 )
    return 1;
  if ( v < 4900 )
    return 2;
  if ( v < 17700 )
    return 3;
  if ( v < 48950 )
    return 4;
  if ( v < 113750 )
    return 5;
  if ( v < 233800 )
    return 6;
  if ( v < 438600 )
    return 7;
  if ( v < 766650 )
    return 8;
  if ( v < 1266650 )
    return 9;
  if ( v < 1998700 )
    return 10;
  if ( v < 3035500 )
    return 11;
  if ( v < 4463550 )
    return 12;
  if ( v < 6384350 )
    return 13;
  if ( v < 8915600 )
    return 14;
  if ( v < 12192400 )
    return 15;
  if ( v < 16368450 )
    return 16;
  if ( v < 21617250 )
    return 17;
  if ( v < 28133300 )
    return 18;
  if ( v < 36133300 )
    return 19;
  if ( v < 49014500 )
    return 20;
  if ( v < 63000600 )
    return 21;
  if ( v < 80977100 )
    return 22;

  return 23;
}
}

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
    textualRank_.setString( MenAmongGods::rankToString[ points2rank( playerData_.getLook().points ) ] );
    rankSprite_ = gfxCache_.getSprite( 10 + std::min( 20, points2rank( playerData_.getLook().points ) ) );
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