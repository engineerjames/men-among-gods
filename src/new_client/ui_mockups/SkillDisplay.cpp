#include "SkillDisplay.h"

SkillDisplay::SkillRow::SkillRow()
    : name_()
    , displayValue_()
    , expRequired_()
{
}

SkillDisplay::SkillDisplay( sf::Font& font )
    : font_( font )
    , skillNames_()
    , initialPosition_( 3, 3 )
{
}

void SkillDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  // Each time we draw a skill we should move down 14 pixels
  //  const sf::Vector2f delta { 0.0f, 14.0f };
  //  skillNames_[ i ].name_.setPosition( initialPosition_ );

  for ( unsigned int i = 0; i < skillNames_.size(); ++i )
  {
    target.draw( skillNames_[ i ].name_, states );
    target.draw( skillNames_[ i ].displayValue_, states );
    target.draw( skillNames_[ i ].expRequired_, states );
  }
}