#include "SkillsAndAttributes.h"

#include "GuiFormatters.h"

// TODO: Fix include directories
#include "../ClientTypes.h"
#include "../ConstantIdentifiers.h"

namespace
{

// clang-format off
skilltab static_skilltab[SkillsAndAttributes::MAX_SKILLS]={
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
}
// clang-format on

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
    , initialAttributePosition_( 3, 1 )
    , initialSkillPosition_( 3, 113 )
    , skillScrollBar_()
{

  skillScrollBar_.setFillColor( sf::Color( 17, 87, 1, 128 ) );
  skillScrollBar_.setOutlineColor( sf::Color::Black );
  skillScrollBar_.setPosition( sf::Vector2f { 207.0f, 149.0f } );
  skillScrollBar_.setSize( sf::Vector2f { 11.0f, 11.0f } );

  for ( unsigned int i = 0; i < MAX_SKILLS; ++i )
  {
    const sf::Vector2f delta { 0.0f, i * 14.0f };

    skills_[ i ].name_.setString( static_skilltab[ i ].name );
    skills_[ i ].displayValue_.setString( "0" );
    skills_[ i ].expRequired_.setString( MenAmongGods::addThousandsSeparator( 1000u ) );
    skills_[ i ].plus_.setString( "+" );
    skills_[ i ].minus_.setString( "-" );

    skills_[ i ].name_.setFont( font_ );
    skills_[ i ].displayValue_.setFont( font_ );
    skills_[ i ].expRequired_.setFont( font_ );
    skills_[ i ].plus_.setFont( font_ );
    skills_[ i ].minus_.setFont( font_ );

    skills_[ i ].name_.setPosition( initialSkillPosition_ + delta );
    skills_[ i ].displayValue_.setPosition( initialSkillPosition_ + sf::Vector2f { 115.0f, delta.y } );
    skills_[ i ].plus_.setPosition( initialSkillPosition_ + sf::Vector2f { 131.0f, delta.y } );
    skills_[ i ].minus_.setPosition( initialSkillPosition_ + sf::Vector2f { 146.0f, delta.y } );
    skills_[ i ].expRequired_.setPosition( initialSkillPosition_ + sf::Vector2f { 165.0f, delta.y } );
  }

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

    attributes_[ i ].name_.setPosition( initialAttributePosition_ + delta );

    attributes_[ i ].displayValue_.setPosition( initialAttributePosition_ + sf::Vector2f { 115.0f, delta.y } );
    attributes_[ i ].plus_.setPosition( initialAttributePosition_ + sf::Vector2f { 131.0f, delta.y } );
    attributes_[ i ].minus_.setPosition( initialAttributePosition_ + sf::Vector2f { 146.0f, delta.y } );
    attributes_[ i ].expRequired_.setPosition( initialAttributePosition_ + sf::Vector2f { 165.0f, delta.y } );

    attributes_[ i ].displayValue_.setString( "0" );
    attributes_[ i ].expRequired_.setString( MenAmongGods::addThousandsSeparator( 1000u ) );
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

  for ( unsigned int i = 0; i < skills_.size(); ++i )
  {
    // TODO: Accomodate scrolling behavior
    if ( i == 10 )
    {
      break;
    }
    target.draw( skills_[ i ].name_, states );
    target.draw( skills_[ i ].displayValue_, states );
    target.draw( skills_[ i ].expRequired_, states );
    target.draw( skills_[ i ].plus_, states );
    target.draw( skills_[ i ].minus_, states );
  }

  // Draw scrollbar
  target.draw( skillScrollBar_, states );
}