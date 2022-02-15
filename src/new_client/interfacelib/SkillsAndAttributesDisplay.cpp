#include "SkillsAndAttributesDisplay.h"

#include "ClientTypes.h"
#include "GuiFormatters.h"
#include "PlayerData.h"
#include "UiPositions.h"
#include "UtilityFunctions.h"

#include <iostream>

// Commands
#include "SkillCommand.h"

namespace
{

int attrib_needed( int n, int v, cplayer& pl )
{
  if ( v >= pl.attrib[ n ][ 2 ] )
  {
    return std::numeric_limits< int >::max();
  }

  return v * v * v * pl.attrib[ n ][ 3 ] / 20;
}

int skill_needed( int n, int v, cplayer& pl )
{
  if ( v >= pl.skill[ n ][ 2 ] )
  {
    return std::numeric_limits< int >::max();
  }

  return std::max( v, v * v * v * pl.skill[ n ][ 3 ] / 40 );
}

// clang-format off
skilltab static_skilltab[MAX_SKILLS]={
	{0,     'C',    "Hand to Hand", "Fighting without weapons.",                    {AT_BRAVE,AT_AGIL,AT_STREN}},
	{1,     'C',    "Karate",       "Fighting without weapons and doing damage.",   {AT_BRAVE,AT_AGIL,AT_STREN}},
	{2,     'C',    "Dagger",       "Fighting with daggers or similiar weapons.",   {AT_BRAVE,AT_AGIL,AT_INT}},
	{3,     'C',    "Sword",        "Fighting with swords or similiar weapons.",    {AT_BRAVE,AT_AGIL,AT_STREN}},
	{4,     'C',    "Axe",          "Fighting with axes or similiar weapons.",      {AT_BRAVE,AT_STREN,AT_STREN}},
	{5,     'C',    "Staff",        "Fighting with staffs or similiar weapons.",    {AT_AGIL,AT_STREN,AT_STREN}},
	{6,     'C',    "Two-Handed",   "Fighting with two-handed weapons.",            {AT_AGIL,AT_STREN,AT_STREN}},

	{7,     'G',    "Lock-Picking", "Opening doors without keys.",                  {AT_INT,AT_WILL,AT_AGIL}},
	{8,     'G',    "Stealth",      "Moving without being seen or heard.",          {AT_INT,AT_WILL,AT_AGIL}},
	{9,     'G',    "Perception",   "Seeing and hearing.",                          {AT_INT,AT_WILL,AT_AGIL}},

	{10,    'M',    "Swimming",     "Moving through water without drowning.",       {AT_INT,AT_WILL,AT_AGIL}},
	{11,    'R',    "Magic Shield", "Spell: Create a magic shield (Cost: 25 Mana).",  {AT_BRAVE,AT_INT,AT_WILL}},

	{12,    'G',    "Bartering",    "Getting good prices from merchants.",          {AT_BRAVE,AT_INT,AT_WILL}},
	{13,    'G',    "Repair",       "Repairing items.",                             {AT_INT,AT_WILL,AT_AGIL}},

	{14,    'R',    "Light",        "Spell: Create light (Cost: 5 Mana).",           {AT_BRAVE,AT_INT,AT_WILL}},
	{15,    'R',    "Recall",       "Spell: Teleport to temple (Cost: 15 Mana).",    {AT_BRAVE,AT_INT,AT_WILL}},
	{16,    'R',    "Guardian Angel","Spell: Avoid loss of HPs and items on death.", {AT_BRAVE,AT_INT,AT_WILL}},
	{17,    'R',    "Protection",   "Spell: Enhance Armor of target (Cost: 15 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{18,    'R',    "Enhance Weapon","Spell: Enhance Weapon of target (Cost: 15 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{19,    'R',    "Stun",         "Spell: Make target motionless (Cost: 20 Mana).",   {AT_BRAVE,AT_INT,AT_WILL}},
	{20,    'R',    "Curse",        "Spell: Decrease attributes of target (Cost: 35 Mana).",  {AT_BRAVE,AT_INT,AT_WILL}},
	{21,    'R',    "Bless",        "Spell: Increase attributes of target (Cost: 35 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{22,    'R',    "Identify",     "Spell: Read stats of item/character. (Cost: 25 Mana)",   {AT_BRAVE,AT_INT,AT_WILL}},

	{23,    'G',    "Resistance",   "Resist against magic.",                        {AT_INT,AT_WILL,AT_STREN}},

	{24,    'R',    "Blast",        "Spell: Inflict injuries to target (Cost: varies).", {AT_INT,AT_WILL,AT_STREN}},
	{25,    'R',    "Dispel Magic", "Spell: Removes curse magic from target (Cost: 25 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},

	{26,    'R',    "Heal",         "Spell: Heal injuries (Cost: 25 Mana).",         {AT_BRAVE,AT_INT,AT_WILL}},
	{27,    'R',    "Ghost Companion","Spell: Create a ghost to attack an enemy.",    {AT_BRAVE,AT_INT,AT_WILL}},

	{28,    'B',    "Regenerate",   "Regenerate Hitpoints faster.",                 {AT_STREN,AT_STREN,AT_STREN}},
	{29,    'B',    "Rest",         "Regenerate Endurance faster.",                 {AT_AGIL,AT_AGIL,AT_AGIL}},
	{30,    'B',    "Meditate",     "Regenerate Mana faster.",                      {AT_INT,AT_WILL,AT_WILL}},

	{31,    'G',    "Sense Magic",  "Find out who casts what at you.",              {AT_BRAVE,AT_INT,AT_WILL}},
	{32,    'G',    "Immunity",     "Partial immunity against negative magic.",     {AT_BRAVE,AT_AGIL,AT_STREN}},
	{33,    'G',    "Surround Hit", "Hit all your enemies at once.",                {AT_BRAVE,AT_AGIL,AT_STREN}},
	{34,    'G',    "Concentrate",  "Reduces mana cost for all spells.",            {AT_WILL,AT_WILL,AT_WILL}},
	{35,    'G',    "Warcry",       "Frighten all enemies in hearing distance.",    {AT_BRAVE,AT_BRAVE,AT_STREN}},

	{36,   'Z',   "", "", {0,0,0,}},
	{37,   'Z',   "", "", {0,0,0,}},
	{38,   'Z',   "", "", {0,0,0,}},
	{39,   'Z',   "", "", {0,0,0,}},

	{40,   'Z',   "", "", {0,0,0,}},
	{41,   'Z',   "", "", {0,0,0,}},
	{42,   'Z',   "", "", {0,0,0,}},
	{43,   'Z',   "", "", {0,0,0,}},
	{44,   'Z',   "", "", {0,0,0,}},
	{45,   'Z',   "", "", {0,0,0,}},
	{46,   'Z',   "", "", {0,0,0,}},
	{47,   'Z',   "", "", {0,0,0,}},
	{48,   'Z',   "", "", {0,0,0,}},
	{49,   'Z',   "", "", {0,0,0,}}};
// clang-format on

int getSkillNumber( std::string skillName )
{
  skilltab* foundSkill = nullptr;

  for ( int i = 0; i < MAX_SKILLS; ++i )
  {
    if ( static_skilltab[ i ].name == skillName )
    {
      foundSkill = &static_skilltab[ i ];
      break;
    }
  }

  if ( foundSkill )
  {
    return foundSkill->nr;
  }

  return -1; // TODO: Find something better than a negative return sentinel value
}

int getBaseAttributeModifier( const std::string& skillName )
{
  for ( unsigned int i = 0; i < MAX_SKILLS; ++i )
  {
    if ( static_skilltab[ i ].name == skillName )
    {
      return static_skilltab[ i ].attrib[ 0 ];
    }
  }

  return -1;
}

} // namespace

namespace MenAmongGods
{
SkillsAndAttributesDisplay::SkillRow::SkillRow()
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

SkillsAndAttributesDisplay::SkillsAndAttributesDisplay( const sf::RenderWindow& window, const sf::Font& font, PlayerData& playerData )
    : window_( window )
    , font_( font )
    , playerData_( playerData )
    , attributes_()
    , skills_()
    , skillsToDisplay_()
    , skillScrollBar_()
    , scrollUpBox_( MenAmongGods::scrollUpBoxPosition, MenAmongGods::scrollBoxSize )
    , scrollDownBox_( MenAmongGods::scrollDownBoxPosition, MenAmongGods::scrollBoxSize )
    , scrollPosition_( 0 )
    , initialScrollBarPosition_( 207.0f, 149.0f )
{

  skillScrollBar_.setFillColor( sf::Color( 17, 87, 1, 128 ) );
  skillScrollBar_.setOutlineColor( sf::Color::Black );
  skillScrollBar_.setPosition( initialScrollBarPosition_ );
  skillScrollBar_.setSize( sf::Vector2f { 11.0f, 11.0f } );

  for ( unsigned int i = 0; i < MAX_SKILLS; ++i )
  {
    const sf::Vector2f delta { 0.0f, i * 14.0f };

    skills_[ i ].name_.setString( static_skilltab[ i ].name );
    skills_[ i ].displayValue_.setString( "0" );
    skills_[ i ].expRequired_.setString( MenAmongGods::addThousandsSeparator( 1000u ) );

    skills_[ i ].name_.setFont( font_ );
    skills_[ i ].displayValue_.setFont( font_ );
    skills_[ i ].expRequired_.setFont( font_ );
    skills_[ i ].plus_.setFont( font_ );
    skills_[ i ].minus_.setFont( font_ );

    skills_[ i ].name_.setPosition( MenAmongGods::initialSkillPosition + delta );
    skills_[ i ].displayValue_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 127.0f, delta.y } );
    skills_[ i ].plus_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 131.0f, delta.y } );
    skills_[ i ].minus_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 146.0f, delta.y } );
    skills_[ i ].expRequired_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 200.0f, delta.y } );

    skills_[ i ].displayValue_.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );
    skills_[ i ].expRequired_.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );
  }

  attributes_[ 0 ].name_.setString( "Braveness" );
  attributes_[ 1 ].name_.setString( "Willpower" );
  attributes_[ 2 ].name_.setString( "Intuition" );
  attributes_[ 3 ].name_.setString( "Agility" );
  attributes_[ 4 ].name_.setString( "Strength" );

  // Position attributes according to legacy layout
  for ( unsigned int i = 0; i < attributes_.size(); ++i )
  {
    const sf::Vector2f delta { 0.0f, i * 14.0f };

    attributes_[ i ].name_.setPosition( MenAmongGods::initialAttributePosition + delta );

    attributes_[ i ].displayValue_.setPosition( MenAmongGods::initialAttributePosition + sf::Vector2f { 127.0f, delta.y } );
    attributes_[ i ].plus_.setPosition( MenAmongGods::initialAttributePosition + sf::Vector2f { 131.0f, delta.y } );
    attributes_[ i ].minus_.setPosition( MenAmongGods::initialAttributePosition + sf::Vector2f { 146.0f, delta.y } );
    attributes_[ i ].expRequired_.setPosition( MenAmongGods::initialAttributePosition + sf::Vector2f { 200.0f, delta.y } );

    attributes_[ i ].displayValue_.setString( "0" );
    attributes_[ i ].expRequired_.setString( MenAmongGods::addThousandsSeparator( 1000u ) );

    attributes_[ i ].name_.setFont( font_ );
    attributes_[ i ].displayValue_.setFont( font_ );
    attributes_[ i ].expRequired_.setFont( font_ );
    attributes_[ i ].plus_.setFont( font_ );
    attributes_[ i ].minus_.setFont( font_ );

    attributes_[ i ].displayValue_.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );
    attributes_[ i ].expRequired_.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );
  }
}

void SkillsAndAttributesDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( unsigned int i = 0; i < attributes_.size(); ++i )
  {
    target.draw( attributes_[ i ].name_, states );
    target.draw( attributes_[ i ].displayValue_, states );
    target.draw( attributes_[ i ].expRequired_, states );
    target.draw( attributes_[ i ].plus_, states );
    target.draw( attributes_[ i ].minus_, states );
  }

  for ( unsigned int i = 0; i < skillsToDisplay_.size(); ++i )
  {
    if ( i == 10 || skillsToDisplay_[ i ] == nullptr )
    {
      break;
    }

    target.draw( skillsToDisplay_[ i ]->name_, states );
    target.draw( skillsToDisplay_[ i ]->displayValue_, states );
    target.draw( skillsToDisplay_[ i ]->expRequired_, states );
    target.draw( skillsToDisplay_[ i ]->plus_, states );
    target.draw( skillsToDisplay_[ i ]->minus_, states );
  }

  // Draw scrollbar
  target.draw( skillScrollBar_, states );
}

void SkillsAndAttributesDisplay::update()
{
  cplayer& player = playerData_.getClientSidePlayerInfo();

  // Attributes
  for ( unsigned int i = 0; i < MAX_ATTRIBUTES; ++i )
  {
    attributes_[ i ].displayValue_.setString( std::to_string( player.attrib[ i ][ 5 ] ) );
    attributes_[ i ].expRequired_.setString( std::to_string( attrib_needed( i, player.attrib[ i ][ 0 ], player ) ) );
    attributes_[ i ].displayValue_.update();
    attributes_[ i ].expRequired_.update();

    if ( player.points >= attrib_needed( i, player.attrib[ i ][ 0 ], player ) )
    {
      attributes_[ i ].plus_.setString( "+" );
    }
  }

  // Skills
  // We iterate across all skills, but only set the position of the ones we're going to render,
  // since not all skills are displayed at all times (only when you get 'Bless' for instance, is the
  // skill displayed.)

  skillsToDisplay_.fill( nullptr );
  unsigned int j = 0;
  for ( unsigned int i = scrollPosition_; i < MAX_SKILLS; ++i )
  {
    // Player does not have the inspected skill
    if ( player.skill[ i ][ 0 ] == 0 )
    {
      continue;
    }

    // Player DOES have the skill, so appropriately set the delta value (based on how many skills)
    // we've added to the skillstodisplay list.
    skillsToDisplay_[ j ] = &skills_[ i ];
    const sf::Vector2f delta { 0.0f, j * 14.0f };
    j++;

    skills_[ i ].displayValue_.setString( std::to_string( player.skill[ i ][ 5 ] ) );
    skills_[ i ].expRequired_.setString( std::to_string( skill_needed( i, player.skill[ i ][ 0 ], player ) ) );
    skills_[ i ].name_.setPosition( MenAmongGods::initialSkillPosition + delta );

    skills_[ i ].displayValue_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 127.0f, delta.y } );
    skills_[ i ].plus_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 131.0f, delta.y } );
    skills_[ i ].minus_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 146.0f, delta.y } );
    skills_[ i ].expRequired_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 200.0f, delta.y } );

    skills_[ i ].displayValue_.update();
    skills_[ i ].expRequired_.update();

    if ( player.points >= skill_needed( i, player.skill[ i ][ 0 ], player ) )
    {
      skills_[ i ].plus_.setString( "+" );
    }
  }
  skillScrollBar_.setPosition( initialScrollBarPosition_ + MenAmongGods::scrollBarMovementPerClick );
}

void SkillsAndAttributesDisplay::onUserInput( const sf::Event& e )
{
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( scrollUpBox_.contains( mousePosition ) )
    {
      if ( scrollPosition_ > 0 )
      {
        scrollPosition_--;
      }
    }

    if ( scrollDownBox_.contains( mousePosition ) )
    {
      scrollPosition_++;
    }

    // 10 skills displayable at most
    for ( int i = 0; i < 10; ++i )
    {
      const sf::Vector2f  delta { 0.0f, i * 14.0f };
      const sf::Vector2f  potentialSkillPosition = initialSkillPosition + delta;
      const sf::Vector2f  skillBarSize { 105.0f, 10.0f };
      const sf::FloatRect clickableSkillRegion { potentialSkillPosition, skillBarSize };

      if ( clickableSkillRegion.contains( mousePosition ) )
      {
        int  skillNr               = getSkillNumber( skillsToDisplay_[ i ]->name_.getString() );
        int  baseAttributeModifier = getBaseAttributeModifier( skillsToDisplay_[ i ]->name_.getString() );
        auto skillCommand          = std::make_shared< SkillCommand >( static_cast< unsigned int >( skillNr ), 0,
                                                              static_cast< unsigned int >( baseAttributeModifier ) );

        commands_.push_back( skillCommand );
      }
    }
  }
}

void SkillsAndAttributesDisplay::finalize()
{
}
} // namespace MenAmongGods