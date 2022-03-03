#include "SkillsAndAttributesDisplay.h"

#include "ClientTypes.h"
#include "ColorPalette.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "GuiFormatters.h"
#include "PlayerData.h"
#include "UiPositions.h"
#include "UtilityFunctions.h"

#include <iostream>

// Commands
#include "SkillCommand.h"
#include "StatCommand.h"

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
    , skillsIndex_( 0 )
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

SkillsAndAttributesDisplay::SkillsAndAttributesDisplay( const sf::RenderWindow& window, const sf::Font& font, GraphicsCache& gfxCache,
                                                        const GraphicsIndex& gfxIndex, PlayerData& playerData )
    : window_( window )
    , font_( font )
    , gfxCache_( gfxCache )
    , gfxIndex_( gfxIndex )
    , playerData_( playerData )
    , attributes_()
    , skills_()
    , skillsToDisplay_()
    , skillScrollBar_()
    , scrollUpBox_( MenAmongGods::scrollUpBoxPosition, MenAmongGods::scrollBoxSize )
    , scrollDownBox_( MenAmongGods::scrollDownBoxPosition, MenAmongGods::scrollBoxSize )
    , scrollPosition_( 0 )
    , initialScrollBarPosition_( 207.0f, 149.0f )
    , spellsToDraw()
    , expToSpendLabel_( "Update", font, FONT_SIZE )
    , expToSpendValue_()
    , raiseMap_()
    , totalPointsToSpend_()
{

  expToSpendLabel_.setPosition( MenAmongGods::expToSpendLabelPosition );
  expToSpendValue_.setPosition( MenAmongGods::expToSpendValuePosition );

  expToSpendLabel_.setFont( font_ );
  expToSpendValue_.setFont( font_ );

  expToSpendLabel_.setCharacterSize( FONT_SIZE );
  expToSpendValue_.setCharacterSize( FONT_SIZE );

  expToSpendLabel_.setFillColor( MenAmongGods::MsgYellow );
  expToSpendValue_.setFillColor( MenAmongGods::MsgYellow );

  expToSpendLabel_.setOutlineColor( sf::Color::Black );
  expToSpendValue_.setOutlineColor( sf::Color::Black );

  expToSpendValue_.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );

  expToSpendLabel_.setString( "Update" );
  expToSpendValue_.setString( MenAmongGods::addThousandsSeparator( 1234251u ) );

  skillScrollBar_.setFillColor( MenAmongGods::ScrollBarGreen );
  skillScrollBar_.setOutlineColor( sf::Color::Black );
  skillScrollBar_.setPosition( initialScrollBarPosition_ );
  skillScrollBar_.setSize( sf::Vector2f { 11.0f, 11.0f } );

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
}

void SkillsAndAttributesDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{

  target.draw( expToSpendLabel_, states );
  target.draw( expToSpendValue_, states );

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

  for ( const auto& t : lifeDisplay_ )
  {
    target.draw( t.name_, states );
    target.draw( t.displayValue_, states );
    target.draw( t.expRequired_, states );
    target.draw( t.plus_, states );
    target.draw( t.minus_, states );
  }

  // Draw scrollbar
  target.draw( skillScrollBar_, states );

  // Draw active spells
  for ( const auto& s : spellsToDraw )
  {
    target.draw( s, states );
  }
}

void SkillsAndAttributesDisplay::update()
{
  cplayer& player = playerData_.getClientSidePlayerInfo();

  // Super hacky: TODO: change this data structure to match to something more appropriate
  auto raiseMapCopy = raiseMap_;
  int  totalSpent {};
  for ( auto& [ skillOrAttributeName, raiseStack ] : raiseMapCopy )
  {
    while ( ! raiseStack.empty() )
    {
      totalSpent += raiseStack.top();
      raiseStack.pop();
    }
  }

  totalPointsToSpend_ = player.points;
  totalPointsToSpend_ -= totalSpent;

  expToSpendValue_.setString( addThousandsSeparator( totalPointsToSpend_ ) );

  // Attributes
  for ( unsigned int i = 0; i < MAX_ATTRIBUTES; ++i )
  {
    int nTimesRaised = static_cast< int >( raiseMap_[ attributes_[ i ].name_.getString() ].size() );

    attributes_[ i ].displayValue_.setString( std::to_string( player.attrib[ i ][ 5 ] + nTimesRaised ) );

    int expNeededToRaise = attrib_needed( i, player.attrib[ i ][ 0 ] + nTimesRaised, player );

    if ( expNeededToRaise == std::numeric_limits< int >::max() )
    {
      attributes_[ i ].expRequired_.setString( "" );
    }
    else
    {
      attributes_[ i ].expRequired_.setString( MenAmongGods::addThousandsSeparator( expNeededToRaise ) );
    }

    attributes_[ i ].displayValue_.update();
    attributes_[ i ].expRequired_.update();

    if ( totalPointsToSpend_ >= attrib_needed( i, player.attrib[ i ][ 0 ] + nTimesRaised, player ) )
    {
      attributes_[ i ].plus_.setString( "+" );
    }
    else
    {
      attributes_[ i ].plus_.setString( "" );
    }

    if ( nTimesRaised > 0 )
    {
      attributes_[ i ].minus_.setString( "-" );
    }
    else
    {
      attributes_[ i ].minus_.setString( "" );
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
    skillsToDisplay_[ j ]               = &skills_[ i ];
    skillsToDisplay_[ j ]->skillsIndex_ = i;
    const sf::Vector2f delta { 0.0f, j * 14.0f };
    j++;

    int nTimesRaised = static_cast< int >( raiseMap_[ skills_[ i ].name_.getString() ].size() );

    skills_[ i ].displayValue_.setString( std::to_string( player.skill[ i ][ 5 ] + nTimesRaised ) );

    int expNeededToRaise = skill_needed( i, player.skill[ i ][ 0 ] + nTimesRaised, player );
    if ( expNeededToRaise == std::numeric_limits< int >::max() )
    {
      skills_[ i ].expRequired_.setString( "" );
    }
    else
    {
      skills_[ i ].expRequired_.setString( MenAmongGods::addThousandsSeparator( expNeededToRaise ) );
    }

    skills_[ i ].name_.setPosition( MenAmongGods::initialSkillPosition + delta );

    skills_[ i ].displayValue_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 127.0f, delta.y } );
    skills_[ i ].plus_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 131.0f, delta.y } );
    skills_[ i ].minus_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 146.0f, delta.y } );
    skills_[ i ].expRequired_.setPosition( MenAmongGods::initialSkillPosition + sf::Vector2f { 200.0f, delta.y } );

    skills_[ i ].displayValue_.update();
    skills_[ i ].expRequired_.update();

    if ( totalPointsToSpend_ >= skill_needed( i, player.skill[ i ][ 0 ] + nTimesRaised, player ) )
    {
      skills_[ i ].plus_.setString( "+" );
    }
    else
    {
      skills_[ i ].plus_.setString( "" );
    }

    if ( nTimesRaised > 0 )
    {
      skills_[ i ].minus_.setString( "-" );
    }
    else
    {
      skills_[ i ].minus_.setString( "" );
    }
  }
  skillScrollBar_.setPosition( initialScrollBarPosition_ +
                               static_cast< float >( scrollPosition_ ) * MenAmongGods::scrollBarMovementPerClick );

  // Update spells to draw
  spellsToDraw.clear();
  const cplayer& pl = playerData_.getClientSidePlayerInfo();

  for ( int n = 0; n < 20; n++ )
  {
    if ( pl.spell[ n ] != 0 )
    {
      sf::Vector2f spellPosition { static_cast< float >( 374 + ( n % 5 ) * 24 ), static_cast< float >( 4 + ( n / 5 ) * 24 ) };

      spellsToDraw.push_back( gfxCache_.getSprite( pl.spell[ n ] ) );

      auto lastSprite = ( spellsToDraw.end() - 1 );
      lastSprite->setPosition( spellPosition );

      // Set the transparency of the sprite based on the 'active' value.
      std::uint8_t alpha = 255 * ( pl.active[ n ] ) / 15;
      lastSprite->setColor( sf::Color { 255u, 255u, 255u, alpha } );
    }
  }

  expToSpendValue_.update();

  // TODO: Reduce massive amounts of code duplication here

  // Update HP
  int nTimesRaisedHp = static_cast< int >( raiseMap_[ lifeDisplay_[ 0 ].name_.getString() ].size() );
  lifeDisplay_[ 0 ].displayValue_.setString( std::to_string( playerData_.getClientSidePlayerInfo().a_hp ) );

  int expNeededToRaiseHp = hp_needed( player.hp[ 0 ] + nTimesRaisedHp, player );
  if ( expNeededToRaiseHp == std::numeric_limits< int >::max() )
  {
    lifeDisplay_[ 0 ].expRequired_.setString( "" );
  }
  else
  {
    lifeDisplay_[ 0 ].expRequired_.setString( MenAmongGods::addThousandsSeparator( expNeededToRaiseHp ) );
  }

  lifeDisplay_[ 0 ].displayValue_.update();
  lifeDisplay_[ 0 ].expRequired_.update();

  if ( totalPointsToSpend_ >= expNeededToRaiseHp )
  {
    lifeDisplay_[ 0 ].plus_.setString( "+" );
  }
  else
  {
    lifeDisplay_[ 0 ].plus_.setString( "" );
  }

  if ( nTimesRaisedHp > 0 )
  {
    lifeDisplay_[ 0 ].minus_.setString( "-" );
  }
  else
  {
    lifeDisplay_[ 0 ].minus_.setString( "" );
  }

  // Update End
  int nTimesRaisedEnd = static_cast< int >( raiseMap_[ lifeDisplay_[ 1 ].name_.getString() ].size() );
  lifeDisplay_[ 1 ].displayValue_.setString( std::to_string( playerData_.getClientSidePlayerInfo().a_end ) );

  int expNeededToRaiseEnd = end_needed( player.end[ 0 ] + nTimesRaisedEnd, player );
  if ( expNeededToRaiseEnd == std::numeric_limits< int >::max() )
  {
    lifeDisplay_[ 1 ].expRequired_.setString( "" );
  }
  else
  {
    lifeDisplay_[ 1 ].expRequired_.setString( MenAmongGods::addThousandsSeparator( expNeededToRaiseEnd ) );
  }

  lifeDisplay_[ 1 ].displayValue_.update();
  lifeDisplay_[ 1 ].expRequired_.update();

  if ( totalPointsToSpend_ >= end_needed( expNeededToRaiseEnd, player ) )
  {
    lifeDisplay_[ 1 ].plus_.setString( "+" );
  }
  else
  {
    lifeDisplay_[ 1 ].plus_.setString( "" );
  }

  if ( nTimesRaisedEnd > 0 )
  {
    lifeDisplay_[ 1 ].minus_.setString( "-" );
  }
  else
  {
    lifeDisplay_[ 1 ].minus_.setString( "" );
  }

  // Update Mana
  int nTimesRaisedMana = static_cast< int >( raiseMap_[ lifeDisplay_[ 2 ].name_.getString() ].size() );
  lifeDisplay_[ 2 ].displayValue_.setString( std::to_string( playerData_.getClientSidePlayerInfo().a_mana ) );

  int expNeededToRaiseMana = mana_needed( player.mana[ 0 ] + nTimesRaisedMana, player );
  if ( expNeededToRaiseMana == std::numeric_limits< int >::max() )
  {
    lifeDisplay_[ 2 ].expRequired_.setString( "" );
  }
  else
  {
    lifeDisplay_[ 2 ].expRequired_.setString( MenAmongGods::addThousandsSeparator( expNeededToRaiseMana ) );
  }

  lifeDisplay_[ 2 ].displayValue_.update();
  lifeDisplay_[ 2 ].expRequired_.update();

  if ( totalPointsToSpend_ >= mana_needed( player.mana[ 0 ] + nTimesRaisedMana, player ) )
  {
    lifeDisplay_[ 2 ].plus_.setString( "+" );
  }
  else
  {
    lifeDisplay_[ 2 ].plus_.setString( "" );
  }

  if ( nTimesRaisedMana > 0 )
  {
    lifeDisplay_[ 2 ].minus_.setString( "-" );
  }
  else
  {
    lifeDisplay_[ 2 ].minus_.setString( "" );
  }
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
        if ( skillsToDisplay_[ i ] == nullptr )
        {
          return;
        }

        int  skillNr               = getSkillNumber( skillsToDisplay_[ i ]->name_.getString() );
        int  baseAttributeModifier = getBaseAttributeModifier( skillsToDisplay_[ i ]->name_.getString() );
        auto skillCommand = std::make_shared< SkillCommand >( static_cast< unsigned int >( skillNr ), playerData_.getSelectedCharacter(),
                                                              static_cast< unsigned int >( baseAttributeModifier ) );

        commands_.push_back( skillCommand );
      }
    }

    // Check if a +/- area was clicked
    if ( MenAmongGods::plusAreaRectangle.contains( mousePosition ) )
    {
      // Find out which row was clicked -- each row
      int row         = static_cast< int >( ( mousePosition.y / 14.0f ) );
      row             = std::max( 0, row ); // 0 - 4 attributes, 5-7 hp/end/mana, the rest are skills
      cplayer& player = playerData_.getClientSidePlayerInfo();

      if ( row >= 0 && row <= 4 ) // Attributes
      {
        int nTimesRaised   = static_cast< int >( raiseMap_[ attributes_[ row ].name_.getString() ].size() );
        int pointsRequired = attrib_needed( row, player.attrib[ row ][ 0 ] + nTimesRaised, player );
        if ( totalPointsToSpend_ >= pointsRequired )
        {
          std::string attributeName = attributes_.at( row ).name_.getString();

          raiseMap_[ attributeName ].push( pointsRequired );
        }
      }
      else if ( row >= 5 && row <= 7 ) // HP/END/MANA
      {
        if ( row == 5 ) // hp
        {
          int nTimesRaised   = static_cast< int >( raiseMap_[ lifeDisplay_[ 0 ].name_.getString() ].size() );
          int pointsRequired = hp_needed( player.hp[ 0 ] + nTimesRaised, player );
          if ( totalPointsToSpend_ >= pointsRequired )
          {
            std::string hpManaEndName = lifeDisplay_.at( 0 ).name_.getString();

            raiseMap_[ hpManaEndName ].push( pointsRequired );
          }
        }
        else if ( row == 6 ) // end
        {
          int nTimesRaised   = static_cast< int >( raiseMap_[ lifeDisplay_[ 1 ].name_.getString() ].size() );
          int pointsRequired = end_needed( player.end[ 0 ] + nTimesRaised, player );
          if ( totalPointsToSpend_ >= pointsRequired )
          {
            std::string hpManaEndName = lifeDisplay_.at( 1 ).name_.getString();

            raiseMap_[ hpManaEndName ].push( pointsRequired );
          }
        }
        else if ( row == 7 ) // mana
        {
          int nTimesRaised   = static_cast< int >( raiseMap_[ lifeDisplay_[ 2 ].name_.getString() ].size() );
          int pointsRequired = mana_needed( player.mana[ 0 ] + nTimesRaised, player );
          if ( totalPointsToSpend_ >= pointsRequired )
          {
            std::string hpManaEndName = lifeDisplay_.at( 2 ).name_.getString();

            raiseMap_[ hpManaEndName ].push( pointsRequired );
          }
        }
      }
      else // Skills
      {
        if ( skillsToDisplay_[ row - 8 ] == nullptr )
        {
          return;
        }

        int m            = skillsToDisplay_[ row - 8 ]->skillsIndex_;
        int nTimesRaised = static_cast< int >( raiseMap_[ skillsToDisplay_[ row - 8 ]->name_.getString() ].size() );

        int pointsRequired = skill_needed( m, player.skill[ m ][ 0 ] + nTimesRaised, player );
        if ( totalPointsToSpend_ >= pointsRequired )
        {
          std::string skillName = skillsToDisplay_[ row - 8 ]->name_.getString();

          raiseMap_[ skillName ].push( pointsRequired );
        }
      }
    }
    else if ( MenAmongGods::minusAreaRectangle.contains( mousePosition ) )
    {
      // Find out which row was clicked -- each row
      int row = static_cast< int >( mousePosition.y / 14.0f );
      row     = std::max( 0, row );

      if ( row >= 0 && row <= 4 ) // Attributes
      {
        std::string attributeName = attributes_.at( row ).name_.getString();
        if ( raiseMap_.count( attributeName ) != 0 && raiseMap_[ attributeName ].size() > 0 )
        {
          raiseMap_[ attributeName ].pop();
        }
      }
      else if ( row >= 5 && row <= 7 ) // HP/END/MANA
      {
        if ( row == 5 ) // hp
        {
          std::string lifeName = lifeDisplay_.at( 0 ).name_.getString();
          if ( raiseMap_.count( lifeName ) != 0 && raiseMap_[ lifeName ].size() > 0 )
          {
            raiseMap_[ lifeName ].pop();
          }
        }
        else if ( row == 6 ) // mana
        {
          std::string lifeName = lifeDisplay_.at( 1 ).name_.getString();
          if ( raiseMap_.count( lifeName ) != 0 && raiseMap_[ lifeName ].size() > 0 )
          {
            raiseMap_[ lifeName ].pop();
          }
        }
        else if ( row == 7 ) // end
        {
          std::string lifeName = lifeDisplay_.at( 2 ).name_.getString();
          if ( raiseMap_.count( lifeName ) != 0 && raiseMap_[ lifeName ].size() > 0 )
          {
            raiseMap_[ lifeName ].pop();
          }
        }
      }
      else // Skills
      {
        if ( skillsToDisplay_[ row - 8 ] == nullptr )
        {
          return;
        }

        std::string skillName = skillsToDisplay_[ row - 8 ]->name_.getString();
        if ( raiseMap_.count( skillName ) != 0 && raiseMap_[ skillName ].size() > 0 )
        {
          raiseMap_[ skillName ].pop();
        }
      }
    }
    else if ( expToSpendLabel_.getGlobalBounds().contains( mousePosition ) ) // User clicks "Update"
    {
      // Put commands into the command list so we communicate with the server with what we're trying to update
      for ( auto& [ skillOrAttributeName, raiseStack ] : raiseMap_ )
      {
        // The stat number lines up with the attributes perfectly until we reach the skill section.
        // It is at that point that we take the numerical index and ADD 8 to it (vs. subtract).
        // Let's just do it stupidly for now and fix it later.
        int skillNumber {};
        if ( skillOrAttributeName == "Braveness" )
        {
          skillNumber = 0;
        }
        else if ( skillOrAttributeName == "Willpower" )
        {
          skillNumber = 1;
        }
        else if ( skillOrAttributeName == "Intuition" )
        {
          skillNumber = 2;
        }
        else if ( skillOrAttributeName == "Agility" )
        {
          skillNumber = 3;
        }
        else if ( skillOrAttributeName == "Strength" )
        {
          skillNumber = 4;
        }
        else if ( skillOrAttributeName == "Hitpoints" )
        {
          skillNumber = 5;
        }
        else if ( skillOrAttributeName == "Endurance" )
        {
          skillNumber = 6;
        }
        else if ( skillOrAttributeName == "Mana" )
        {
          skillNumber = 7;
        }
        else // Skill
        {
          skillNumber = getSkillNumber( skillOrAttributeName ) + 8;
        }

        LOG_DEBUG( "Attempting to update " << skillOrAttributeName << " " << raiseStack.size() << " times." );
        commands_.push_back( std::make_shared< MenAmongGods::StatCommand >( static_cast< std::uint16_t >( skillNumber ),
                                                                            static_cast< std::uint32_t >( raiseStack.size() ) ) );

        // Optimistically assume the commands went through
        while ( ! raiseStack.empty() )
        {
          raiseStack.pop();
        }
      }
    }
  }
}

void SkillsAndAttributesDisplay::finalize()
{
  expToSpendValue_.finalize();
}
} // namespace MenAmongGods