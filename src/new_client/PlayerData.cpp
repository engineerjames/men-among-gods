#include "PlayerData.h"

#include <fstream>
#include <iostream>

namespace
{

static constexpr const std::size_t SKILLTAB_SIZE = 50;

// clang-format off
skilltab static_skilltab[SKILLTAB_SIZE]={
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

PlayerData::PlayerData()
    : playerInfo_()
    , playerDataHasChanged_( true ) // Temporarily default to true
    , clientSidePlayerInfo_()
    , okey_()
    , skillsList_( &static_skilltab[ 0 ] )
    , map_( std::make_unique< cmap[] >( MAPX * MAPY ) )
    , look_()
{
  for ( unsigned int i = 0; i < MAPX * MAPY; ++i )
  {
    map_[ i ].ba_sprite = SPR_EMPTY;
  }

  for ( unsigned int i = 0; i < SKILLTAB_SIZE; ++i )
  {
    skillsList_[ i ].attrib[ 0 ] = 1;
  }
}

bool PlayerData::hasPlayerDataChanged() const
{
  return playerDataHasChanged_;
}

const char* PlayerData::getPlayerName() const
{
  return playerInfo_.cname;
}

const char* PlayerData::getPlayerDescription() const
{
  return playerInfo_.desc;
}

void PlayerData::lock()
{
  ioMutex_.lock();
}

void PlayerData::unlock()
{
  ioMutex_.unlock();
}

pdata& PlayerData::getPlayerInfo()
{
  return playerInfo_;
}

cmap* PlayerData::getMap()
{
  return map_.get();
}

skilltab* PlayerData::getSkillList()
{
  return skillsList_;
}

cplayer& PlayerData::getClientSidePlayerInfo()
{
  return clientSidePlayerInfo_;
}

key& PlayerData::getOkey()
{
  return okey_;
}

look& PlayerData::getLook()
{
  return look_;
}

void PlayerData::printMapInformation() const
{
  std::ofstream mapFile( "mapfile.log" );

  if ( mapFile.is_open() )
  {
    for ( unsigned int x = 0; x < MAPX; ++x )
    {
      for ( unsigned int y = 0; y < MAPY; ++y )
      {
        // clang-format off
        mapFile << std::to_string(map_[x + y * MAPX].ba_sprite)
                << ", " << std::to_string( map_[ x + y * MAPX ].x)
                << ", " << std::to_string( map_[ x + y * MAPX ].y)
                << ", " << std::to_string( map_[ x + y * MAPX ].ch_sprite)
                << ", " << std::to_string( map_[ x + y * MAPX ].ch_status)
                << ", " << std::to_string( map_[ x + y * MAPX ].ch_stat_off)
                << ", " << std::to_string( map_[ x + y * MAPX ].ch_speed)
                << ", " << std::to_string( map_[ x + y * MAPX ].ch_nr)
                << ", " << std::to_string( map_[ x + y * MAPX ].ch_id)
                << ", " << std::to_string( map_[ x + y * MAPX ].it_sprite)
                << ", " << std::to_string( map_[ x + y * MAPX ].it_status)
                << ", " << std::to_string( map_[ x + y * MAPX ].back)
                << ", " << std::to_string( map_[ x + y * MAPX ].obj1)
                << ", " << std::to_string( map_[ x + y * MAPX ].obj2)
                << ", " << std::to_string( map_[ x + y * MAPX ].obj_xoff)
                << ", " << std::to_string( map_[ x + y * MAPX ].obj_yoff)
                << ", " << std::to_string( map_[ x + y * MAPX ].ovl_xoff)
                << ", " << std::to_string( map_[ x + y * MAPX ].ovl_yoff)
                << ", " << std::to_string( map_[ x + y * MAPX ].idle_ani)
                << std::endl;
        // clang-format on
      }
    }
  }
  mapFile.close();
}