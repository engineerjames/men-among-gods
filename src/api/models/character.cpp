#include "character.h"

#include <array>

#include "SkillTab.h"

character character::fromJson( const Json::Value& json )
{
  character newChar {};

  newChar.used = json[ "used" ].asInt();

  std::strncpy( newChar.name, json[ "name" ].asString().c_str(), sizeof( newChar.name ) - 1 );
  std::strncpy( newChar.reference, json[ "reference" ].asString().c_str(), sizeof( newChar.reference ) - 1 );
  std::strncpy( newChar.description, json[ "description" ].asString().c_str(), sizeof( newChar.description ) - 1 );

  newChar.kindred = json[ "kindred" ].asInt();
  newChar.player  = json[ "player" ].asInt();
  newChar.pass1   = json[ "pass1" ].asUInt();
  newChar.pass2   = json[ "pass2" ].asUInt();
  newChar.sprite  = json[ "sprite" ].asUInt();
  newChar.sound   = json[ "sound" ].asUInt();

  // TODO: Figure out how to do the flags
  // newChar.flags   = json[ "flags" ].asUInt64();

  newChar.alignment = json[ "alignment" ].asInt();
  newChar.temple_x  = json[ "temple_x" ].asUInt();
  newChar.temple_y  = json[ "temple_y" ].asUInt();
  newChar.tavern_x  = json[ "tavern_x" ].asUInt();
  newChar.tavern_y  = json[ "tavern_y" ].asUInt();
  newChar.temp      = json[ "temp" ].asUInt();

  const Json::Value& jsonAttributes = json[ "attributes" ];
  for ( int i = 0; i < 5; ++i )
  {
    for ( int j = 0; j < 6; ++j )
    {
      newChar.attrib[ i ][ j ] = jsonAttributes[ i ][ "data" ][ j ].asUInt();
    }
  }

  for ( int i = 0; i < 6; ++i )
  {
    newChar.hp[ i ]   = json[ "hp" ][ i ].asUInt();
    newChar.end[ i ]  = json[ "end" ][ i ].asUInt();
    newChar.mana[ i ] = json[ "mana" ][ i ].asUInt();
  }

  const Json::Value& jsonSkills = json[ "skills" ];
  for ( int i = 0; i < 50; ++i )
  {
    for ( int j = 0; j < 6; ++j )
    {
      newChar.skill[ i ][ j ] = jsonSkills[ i ][ "data" ][ j ].asUInt();
    }
  }

  newChar.weapon_bonus = json[ "weapon_bonus" ].asUInt();
  newChar.armor_bonus  = json[ "armor_bonus" ].asUInt();
  newChar.a_hp         = json[ "a_hp" ].asInt();
  newChar.a_end        = json[ "a_end" ].asInt();
  newChar.a_mana       = json[ "a_mana" ].asInt();
  newChar.light        = json[ "light" ].asUInt();
  newChar.mode         = json[ "mode" ].asUInt();
  newChar.speed        = json[ "speed" ].asInt();
  newChar.points       = json[ "points" ].asInt();
  newChar.points_tot   = json[ "points_tot" ].asInt();
  newChar.armor        = json[ "armor" ].asInt();
  newChar.weapon       = json[ "weapon" ].asInt();
  newChar.x            = json[ "x" ].asInt();
  newChar.y            = json[ "y" ].asInt();
  newChar.tox          = json[ "tox" ].asInt();
  newChar.toy          = json[ "toy" ].asInt();
  newChar.frx          = json[ "frx" ].asInt();
  newChar.fry          = json[ "fry" ].asInt();
  newChar.status       = json[ "status" ].asInt();
  newChar.status2      = json[ "status2" ].asInt();
  newChar.dir          = json[ "dir" ].asUInt();
  newChar.gold         = json[ "gold" ].asInt();

  for ( int i = 0; i < 40; ++i )
  {
    newChar.item[ i ] = json[ "item" ][ i ].asUInt();
  }

  for ( int i = 0; i < 20; ++i )
  {
    newChar.worn[ i ]  = json[ "worn" ][ i ].asUInt();
    newChar.spell[ i ] = json[ "spell" ][ i ].asUInt();
  }

  newChar.citem               = json[ "citem" ].asUInt();
  newChar.creation_date       = json[ "creation_date" ].asUInt();
  newChar.login_date          = json[ "login_date" ].asUInt();
  newChar.addr                = json[ "addr" ].asUInt();
  newChar.current_online_time = json[ "current_online_time" ].asUInt();
  newChar.total_online_time   = json[ "total_online_time" ].asUInt();
  newChar.comp_volume         = json[ "comp_volume" ].asUInt();
  newChar.raw_volume          = json[ "raw_volume" ].asUInt();
  newChar.idle                = json[ "idle" ].asUInt();
  newChar.attack_cn           = json[ "attack_cn" ].asUInt();
  newChar.skill_nr            = json[ "skill_nr" ].asUInt();
  newChar.skill_target1       = json[ "skill_target1" ].asUInt();
  newChar.skill_target2       = json[ "skill_target2" ].asUInt();
  newChar.goto_x              = json[ "goto_x" ].asUInt();
  newChar.goto_y              = json[ "goto_y" ].asUInt();
  newChar.use_nr              = json[ "use_nr" ].asUInt();
  newChar.misc_action         = json[ "misc_action" ].asUInt();
  newChar.misc_target1        = json[ "misc_target1" ].asUInt();
  newChar.misc_target2        = json[ "misc_target2" ].asUInt();
  newChar.cerrno              = json[ "cerrno" ].asUInt();
  newChar.escape_timer        = json[ "escape_timer" ].asUInt();

  for ( int i = 0; i < 4; ++i )
  {
    newChar.enemy[ i ] = json[ "enemy" ][ i ].asUInt();
  }

  newChar.current_enemy = json[ "current_enemy" ].asUInt();
  newChar.retry         = json[ "retry" ].asUInt();
  newChar.stunned       = json[ "stunned" ].asUInt();
  newChar.speed_mod     = json[ "speed_mode" ].asInt();
  newChar.last_action   = json[ "last_action" ].asInt();
  newChar.unused        = json[ "unused" ].asInt();
  newChar.depot_sold    = json[ "depot_sold" ].asInt();
  newChar.gethit_dam    = json[ "gethit_dam" ].asInt();
  newChar.gethit_bonus  = json[ "gethit_bonus" ].asInt();
  newChar.light_bonus   = json[ "light_bonus" ].asUInt();

  std::strncpy( newChar.passwd, json[ "password" ].asString().c_str(), sizeof( newChar.passwd ) - 1);

  newChar.lastattack = json[ "lastattack" ].asInt();

  for ( int i = 0; i < 25; ++i )
  {
    newChar.future1[ i ] = json[ "future1" ][ i ].asInt();
  }

  for ( int i = 0; i < 49; ++i )
  {
    newChar.future2[ i ] = json[ "future2" ][ i ].asInt();
  }

  for ( int i = 0; i < 62; ++i )
  {
    newChar.depot[ i ] = json[ "depot" ][ i ].asUInt();
  }

  for ( int i = 0; i < 12; ++i )
  {
    newChar.future3[ i ] = json[ "future3" ][ i ].asInt();
  }

  for ( int i = 0; i < 100; ++i )
  {
    newChar.data[ i ] = json[ "data" ][ i ].asInt();
  }

  for ( int i = 0; i < 10; ++i )
  {
    std::strncpy( newChar.text[ i ], json[ "text" ][ i ].asString().c_str(), sizeof( newChar.text[ i ] ) - 1);
  }

  newChar.sprite_override = json[ "sprite_override" ].asInt();
  newChar.depot_cost      = json[ "depot_cost" ].asInt();
  newChar.luck            = json[ "luck" ].asInt();
  newChar.unreach         = json[ "unreach" ].asInt();
  newChar.unreachx        = json[ "unreach_x" ].asInt();
  newChar.unreachy        = json[ "unreach_y" ].asInt();
  newChar.monsterClass    = json[ "monsterClass" ].asInt();

  return newChar;
}

Json::Value character::toJson() const
{
  Json::Value root {};

  root[ "used" ]                              = used;
  root[ "name" ]                              = name;
  root[ "reference" ]                         = reference;
  root[ "description" ]                       = description;
  root[ "kindred" ]                           = kindred;
  root[ "player" ]                            = player;
  root[ "pass1" ]                             = pass1;
  root[ "pass2" ]                             = pass2;
  root[ "sprite" ]                            = sprite;
  root[ "sound" ]                             = sound;
  root[ "flags" ]                             = Json::objectValue;
  root[ "flags" ][ "immortal" ]               = static_cast< bool >( flags & CF_IMMORTAL );
  root[ "flags" ][ "god" ]                    = static_cast< bool >( flags & CF_GOD );
  root[ "flags" ][ "creator" ]                = static_cast< bool >( flags & CF_CREATOR );
  root[ "flags" ][ "build_mode" ]             = static_cast< bool >( flags & CF_BUILDMODE );
  root[ "flags" ][ "respawn" ]                = static_cast< bool >( flags & CF_RESPAWN );
  root[ "flags" ][ "player" ]                 = static_cast< bool >( flags & CF_PLAYER );
  root[ "flags" ][ "new_user" ]               = static_cast< bool >( flags & CF_NEWUSER );
  root[ "flags" ][ "no_tell" ]                = static_cast< bool >( flags & CF_NOTELL );
  root[ "flags" ][ "no_shout" ]               = static_cast< bool >( flags & CF_NOSHOUT );
  root[ "flags" ][ "merchant" ]               = static_cast< bool >( flags & CF_MERCHANT );
  root[ "flags" ][ "staff" ]                  = static_cast< bool >( flags & CF_STAFF );
  root[ "flags" ][ "no_hp_regen" ]            = static_cast< bool >( flags & CF_NOHPREG );
  root[ "flags" ][ "no_end_regen" ]           = static_cast< bool >( flags & CF_NOENDREG );
  root[ "flags" ][ "no_mana_regen" ]          = static_cast< bool >( flags & CF_NOMANAREG );
  root[ "flags" ][ "invisible" ]              = static_cast< bool >( flags & CF_INVISIBLE );
  root[ "flags" ][ "infrared" ]               = static_cast< bool >( flags & CF_INFRARED );
  root[ "flags" ][ "body" ]                   = static_cast< bool >( flags & CF_BODY );
  root[ "flags" ][ "no_sleep" ]               = static_cast< bool >( flags & CF_NOSLEEP );
  root[ "flags" ][ "undead" ]                 = static_cast< bool >( flags & CF_UNDEAD );
  root[ "flags" ][ "no_magic" ]               = static_cast< bool >( flags & CF_NOMAGIC );
  root[ "flags" ][ "stoned" ]                 = static_cast< bool >( flags & CF_STONED );
  root[ "flags" ][ "usurp" ]                  = static_cast< bool >( flags & CF_USURP );
  root[ "flags" ][ "imp" ]                    = static_cast< bool >( flags & CF_IMP );
  root[ "flags" ][ "shutup" ]                 = static_cast< bool >( flags & CF_SHUTUP );
  root[ "flags" ][ "no_description" ]         = static_cast< bool >( flags & CF_NODESC );
  root[ "flags" ][ "profiler" ]               = static_cast< bool >( flags & CF_PROF );
  root[ "flags" ][ "simple_anim" ]            = static_cast< bool >( flags & CF_SIMPLE );
  root[ "flags" ][ "kicked" ]                 = static_cast< bool >( flags & CF_KICKED );
  root[ "flags" ][ "no_list" ]                = static_cast< bool >( flags & CF_NOLIST );
  root[ "flags" ][ "no_who" ]                 = static_cast< bool >( flags & CF_NOWHO );
  root[ "flags" ][ "spell_ignore" ]           = static_cast< bool >( flags & CF_SPELLIGNORE );
  root[ "flags" ][ "computer_controlled" ]    = static_cast< bool >( flags & CF_CCP );
  root[ "flags" ][ "safe" ]                   = static_cast< bool >( flags & CF_SAFE );
  root[ "flags" ][ "no_staff" ]               = static_cast< bool >( flags & CF_NOSTAFF );
  root[ "flags" ][ "purple_of_honor" ]        = static_cast< bool >( flags & CF_POH );
  root[ "flags" ][ "purple_of_honor_leader" ] = static_cast< bool >( flags & CF_POH_LEADER );
  root[ "flags" ][ "thrall" ]                 = static_cast< bool >( flags & CF_THRALL );
  root[ "flags" ][ "lab_keeper" ]             = static_cast< bool >( flags & CF_LABKEEPER );
  root[ "flags" ][ "is_looting" ]             = static_cast< bool >( flags & CF_ISLOOTING );
  root[ "flags" ][ "golden" ]                 = static_cast< bool >( flags & CF_GOLDEN );
  root[ "flags" ][ "black" ]                  = static_cast< bool >( flags & CF_BLACK );
  root[ "flags" ][ "password" ]               = static_cast< bool >( flags & CF_PASSWD );
  root[ "flags" ][ "update" ]                 = static_cast< bool >( flags & CF_UPDATE );
  root[ "flags" ][ "save_me" ]                = static_cast< bool >( flags & CF_SAVEME );
  root[ "flags" ][ "greater_god" ]            = static_cast< bool >( flags & CF_GREATERGOD );
  root[ "flags" ][ "greater_invisibility" ]   = static_cast< bool >( flags & CF_GREATERINV );
  root[ "alignment" ]                         = alignment;
  root[ "temple_x" ]                          = temple_x;
  root[ "temple_y" ]                          = temple_y;
  root[ "tavern_x" ]                          = tavern_x;
  root[ "tavern_y" ]                          = tavern_y;
  root[ "temp" ]                              = temp;

  root[ "attributes" ]                        = Json::arrayValue;
  std::array< const char*, 5 > attributeNames = { "Braveness", "Willpower", "Intuition", "Agility", "Strength" };
  for ( int i = 0; i < 5; ++i )
  {
    Json::Value attributeRoot {};
    attributeRoot[ "name" ] = attributeNames[ i ];
    attributeRoot[ "data" ] = Json::arrayValue;
    for ( int j = 0; j < 6; ++j )
    {
      attributeRoot[ "data" ].append( attrib[ i ][ j ] );
    }

    root[ "attributes" ].append( attributeRoot );
  }

  root[ "hp" ]   = Json::arrayValue;
  root[ "end" ]  = Json::arrayValue;
  root[ "mana" ] = Json::arrayValue;

  for ( int i = 0; i < 6; ++i )
  {
    root[ "hp" ][ i ]   = hp[ i ];
    root[ "end" ][ i ]  = end[ i ];
    root[ "mana" ][ i ] = mana[ i ];
  }

  root[ "skills" ] = Json::arrayValue;
  for ( int i = 0; i < 50; ++i )
  {
    Json::Value skillRoot {};

    if ( std::string( static_skilltab[ i ].name ).empty() )
    {
      continue;
    }

    skillRoot[ "name" ] = static_skilltab[ i ].name;
    skillRoot[ "data" ] = Json::arrayValue;
    for ( int j = 0; j < 6; ++j )
    {
      skillRoot[ "data" ].append( skill[ i ][ j ] );
    }

    root[ "skills" ].append( skillRoot );
  }

  root[ "weapon_bonus" ] = weapon_bonus;
  root[ "armor_bonus" ]  = armor_bonus;
  root[ "a_hp" ]         = a_hp;
  root[ "a_end" ]        = a_end;
  root[ "a_mana" ]       = a_mana;
  root[ "light" ]        = light;
  root[ "mode" ]         = mode;
  root[ "speed" ]        = speed;
  root[ "points" ]       = points;
  root[ "points_tot" ]   = points;
  root[ "armor" ]        = armor;
  root[ "weapon" ]       = weapon;
  root[ "x" ]            = x;
  root[ "y" ]            = y;
  root[ "tox" ]          = tox;
  root[ "toy" ]          = toy;
  root[ "frx" ]          = frx;
  root[ "fry" ]          = fry;
  root[ "status" ]       = status;
  root[ "status2" ]      = status2;
  root[ "dir" ]          = dir;
  root[ "gold" ]         = gold;

  root[ "item" ] = Json::arrayValue;
  for ( int i = 0; i < 40; ++i )
  {
    root[ "item" ][ i ] = item[ i ];
  }

  root[ "worn" ]  = Json::arrayValue;
  root[ "spell" ] = Json::arrayValue;
  for ( int i = 0; i < 20; ++i )
  {
    root[ "worn" ][ i ]  = worn[ i ];
    root[ "spell" ][ i ] = spell[ i ];
  }

  root[ "citem" ]               = citem;
  root[ "creation_date" ]       = creation_date;
  root[ "login_date" ]          = login_date;
  root[ "addr" ]                = addr;
  root[ "current_online_time" ] = current_online_time;
  root[ "total_online_time" ]   = total_online_time;
  root[ "comp_volume" ]         = comp_volume;
  root[ "raw_volume" ]          = raw_volume;
  root[ "idle" ]                = idle;
  root[ "attack_cn" ]           = attack_cn;
  root[ "skill_nr" ]            = skill_nr;
  root[ "skill_target1" ]       = skill_target1;
  root[ "skill_target2" ]       = skill_target2;
  root[ "goto_x" ]              = goto_x;
  root[ "goto_y" ]              = goto_y;
  root[ "use_nr" ]              = use_nr;
  root[ "misc_action" ]         = misc_action;
  root[ "misc_target1" ]        = misc_target1;
  root[ "misc_target2" ]        = misc_target2;
  root[ "cerrno" ]              = cerrno;
  root[ "escape_timer" ]        = escape_timer;

  root[ "enemy" ] = Json::arrayValue;
  for ( int i = 0; i < 4; ++i )
  {
    root[ "enemy" ][ i ] = enemy[ i ];
  }

  root[ "current_enemy" ] = current_enemy;
  root[ "retry" ]         = retry;
  root[ "stunned" ]       = stunned;
  root[ "speed_mod" ]     = speed_mod;
  root[ "last_action" ]   = last_action;
  root[ "unused" ]        = unused;
  root[ "depot_sold" ]    = depot_sold;
  root[ "gethit_dam" ]    = gethit_dam;
  root[ "gethit_bonus" ]  = gethit_bonus;
  root[ "light_bonus" ]   = light_bonus;
  root[ "password" ]      = std::string( passwd );
  root[ "lastattack" ]    = lastattack;

  root[ "future1" ] = Json::arrayValue;
  root[ "future2" ] = Json::arrayValue;
  root[ "depot" ]   = Json::arrayValue;
  root[ "future3" ] = Json::arrayValue;
  root[ "data" ]    = Json::arrayValue;
  root[ "text" ]    = Json::arrayValue;

  for ( int i = 0; i < 25; ++i )
  {
    root[ "future1" ][ i ] = future1[ i ];
  }

  for ( int i = 0; i < 49; ++i )
  {
    root[ "future2" ][ i ] = future2[ i ];
  }

  for ( int i = 0; i < 62; ++i )
  {
    root[ "depot" ][ i ] = depot[ i ];
  }

  for ( int i = 0; i < 12; ++i )
  {
    root[ "future3" ][ i ] = future3[ i ];
  }

  for ( int i = 0; i < 100; ++i )
  {
    root[ "data" ][ i ] = data[ i ];
  }

  for ( int i = 0; i < 10; ++i )
  {
    root[ "text" ][ i ] = std::string( text[ i ] );
  }

  root[ "sprite_override" ] = sprite_override;
  root[ "depot_cost" ]      = depot_cost;
  root[ "luck" ]            = luck;
  root[ "unreach" ]         = unreach;
  root[ "unreach_x" ]       = unreachx;
  root[ "unreach_y" ]       = unreachy;
  root[ "monsterClass" ]    = monsterClass;

  return root;
}
