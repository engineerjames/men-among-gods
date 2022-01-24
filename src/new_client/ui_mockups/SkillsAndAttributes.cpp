#include "SkillsAndAttributes.h"

SkillsAndAttributes::SkillRow::SkillRow()
    : name_()
    , displayValue_()
    , expRequired_()
    , plus_()
    , minus_()
{
  name_.setOutlineColor( sf::Color::Black );
  displayValue_.setOutlineColor( sf::Color::Black );
  expRequired_.setOutlineColor( sf::Color::Black );
  plus_.setOutlineColor( sf::Color::Black );
  minus_.setOutlineColor( sf::Color::Black );

  name_.setFillColor( MenAmongGods::MsgYellow );
  displayValue_.setFillColor( MenAmongGods::MsgYellow );
  expRequired_.setFillColor( MenAmongGods::MsgYellow );
  plus_.setFillColor( MenAmongGods::MsgYellow );
  minus_.setFillColor( MenAmongGods::MsgYellow );

  name_.setCharacterSize( FONT_SIZE );
  displayValue_.setCharacterSize( FONT_SIZE );
  expRequired_.setCharacterSize( FONT_SIZE );
  plus_.setCharacterSize( FONT_SIZE );
  minus_.setCharacterSize( FONT_SIZE );
}

SkillsAndAttributes::SkillsAndAttributes( const sf::Font& font )
    : font_( font )
    , attributes_()
    , skills_()
    , initialPosition_( 3, 1 )
{

  attributes_[ 0 ].name_.setString( "Braveness" );
  attributes_[ 1 ].name_.setString( "Willpower" );
  attributes_[ 2 ].name_.setString( "Intuition" );
  attributes_[ 3 ].name_.setString( "Agility" );
  attributes_[ 4 ].name_.setString( "Strength" );
  attributes_[ 5 ].name_.setString( "Hitpoints" );
  attributes_[ 6 ].name_.setString( "Endurance" );
  attributes_[ 7 ].name_.setString( "Mana" );

  // Position attributes according to legacy layout
  for ( unsigned int i = 0; i < attributes_.size(); ++i )
  {
    const sf::Vector2f delta { 0.0f, i * 14.0f };

    attributes_[ i ].name_.setPosition( initialPosition_ + delta );

    attributes_[ i ].displayValue_.setPosition( initialPosition_ + sf::Vector2f { 115.0f, delta.y } );
    attributes_[ i ].plus_.setPosition( initialPosition_ + sf::Vector2f { 131.0f, delta.y } );
    attributes_[ i ].minus_.setPosition( initialPosition_ + sf::Vector2f { 146.0f, delta.y } );
    attributes_[ i ].expRequired_.setPosition( initialPosition_ + sf::Vector2f { 165.0f, delta.y } );

    attributes_[ i ].displayValue_.setString( "0" );
    attributes_[ i ].expRequired_.setString( "1,000" );
    attributes_[ i ].plus_.setString( "+" );
    attributes_[ i ].minus_.setString( "-" );

    attributes_[ i ].name_.setFont( font_ );
    attributes_[ i ].displayValue_.setFont( font_ );
    attributes_[ i ].expRequired_.setFont( font_ );
    attributes_[ i ].plus_.setFont( font_ );
    attributes_[ i ].minus_.setFont( font_ );
  }
}

void SkillsAndAttributes::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( unsigned int i = 0; i < attributes_.size(); ++i )
  {
    target.draw( attributes_[ i ].name_, states );
    target.draw( attributes_[ i ].displayValue_, states );
    target.draw( attributes_[ i ].expRequired_, states );
    target.draw( attributes_[ i ].plus_, states );
    target.draw( attributes_[ i ].minus_, states );
  }
}