#include "LifeDisplay.h"

#include "PlayerData.h"
#include "GuiFormatters.h"
#include "UiPositions.h"

namespace
{

int hp_needed( int v, cplayer& pl )
{
  if ( v >= pl.hp[ 2 ] )
  {
    return std::numeric_limits< int >::max();
  }

  return v * pl.hp[ 3 ];
}

int end_needed( int v, cplayer& pl )
{
  if ( v >= pl.end[ 2 ] )
  {
    return std::numeric_limits< int >::max();
  }

  return v * pl.end[ 3 ] / 2;
}

int mana_needed( int v, cplayer& pl )
{
  if ( v >= pl.mana[ 2 ] )
  {
    return std::numeric_limits< int >::max();
  }

  return v * pl.mana[ 3 ];
}
} // namespace

namespace MenAmongGods
{

LifeDisplay::LifeDisplay( const sf::Font& font, PlayerData& playerData )
    : font_( font )
    , playerData_( playerData )
    , lifeDisplay_()
{
  lifeDisplay_[ 0 ].name_.setString( "Hitpoints" );
  lifeDisplay_[ 1 ].name_.setString( "Endurance" );
  lifeDisplay_[ 2 ].name_.setString( "Mana" );

  for ( unsigned int i = 0; i < lifeDisplay_.size(); ++i )
  {
    const sf::Vector2f delta { 0.0f, ( MAX_ATTRIBUTES + i ) * 14.0f };
    lifeDisplay_[ i ].name_.setPosition( MenAmongGods::initialAttributePosition + delta );

    lifeDisplay_[ i ].displayValue_.setPosition( MenAmongGods::initialAttributePosition + sf::Vector2f { 127.0f, delta.y } );
    lifeDisplay_[ i ].plus_.setPosition( MenAmongGods::initialAttributePosition + sf::Vector2f { 131.0f, delta.y } );
    lifeDisplay_[ i ].minus_.setPosition( MenAmongGods::initialAttributePosition + sf::Vector2f { 146.0f, delta.y } );
    lifeDisplay_[ i ].expRequired_.setPosition( MenAmongGods::initialAttributePosition + sf::Vector2f { 200.0f, delta.y } );

    lifeDisplay_[ i ].displayValue_.setString( "0" );
    lifeDisplay_[ i ].expRequired_.setString( MenAmongGods::addThousandsSeparator( 1000u ) );
    lifeDisplay_[ i ].plus_.setString( "+" );
    lifeDisplay_[ i ].minus_.setString( "-" );

    lifeDisplay_[ i ].name_.setFont( font_ );
    lifeDisplay_[ i ].displayValue_.setFont( font_ );
    lifeDisplay_[ i ].expRequired_.setFont( font_ );
    lifeDisplay_[ i ].plus_.setFont( font_ );
    lifeDisplay_[ i ].minus_.setFont( font_ );

    lifeDisplay_[ i ].displayValue_.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );
    lifeDisplay_[ i ].expRequired_.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );
  }
}

void LifeDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( const auto& t : lifeDisplay_ )
  {
    target.draw( t.name_, states );
    target.draw( t.displayValue_, states );
    target.draw( t.expRequired_, states );
    target.draw( t.plus_, states );
    target.draw( t.minus_, states );
  }
}

void LifeDisplay::update()
{
  cplayer& player = playerData_.getClientSidePlayerInfo();
  // Update HP
  lifeDisplay_[ 0 ].displayValue_.setString( std::to_string( playerData_.getClientSidePlayerInfo().a_hp ) );
  lifeDisplay_[ 0 ].expRequired_.setString( MenAmongGods::addThousandsSeparator( hp_needed( player.hp[ 0 ], player ) ) );
  lifeDisplay_[ 0 ].displayValue_.update();
  lifeDisplay_[ 0 ].expRequired_.update();

  // Update End
  lifeDisplay_[ 1 ].displayValue_.setString( std::to_string( playerData_.getClientSidePlayerInfo().a_end ) );
  lifeDisplay_[ 1 ].expRequired_.setString( MenAmongGods::addThousandsSeparator( end_needed( player.end[ 0 ], player ) ) );
  lifeDisplay_[ 1 ].displayValue_.update();
  lifeDisplay_[ 1 ].expRequired_.update();

  // Update Mana
  lifeDisplay_[ 2 ].displayValue_.setString( std::to_string( playerData_.getClientSidePlayerInfo().a_mana ) );
  lifeDisplay_[ 2 ].expRequired_.setString( MenAmongGods::addThousandsSeparator( mana_needed( player.mana[ 0 ], player ) ) );
  lifeDisplay_[ 2 ].displayValue_.update();
  lifeDisplay_[ 2 ].expRequired_.update();
}

void LifeDisplay::onUserInput( const sf::Event& )
{
}

void LifeDisplay::finalize()
{
}

} // namespace MenAmongGods