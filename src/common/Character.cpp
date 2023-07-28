#include "Character.h"

#include <array>
#include <iostream>

#include "Constants.h"
#include "SkillTab.h"

character character::fromJson( const nlohmann::json& json )
{
  character newChar {};

  newChar.used = json[ "used" ].get<int>();

  std::strncpy( newChar.name, json[ "name" ].get<std::string>().c_str(), sizeof( newChar.name ) - 1 );
  std::strncpy( newChar.reference, json[ "reference" ].get<std::string>().c_str(), sizeof( newChar.reference ) - 1 );
  std::strncpy( newChar.description, json[ "description" ].get<std::string>().c_str(), sizeof( newChar.description ) - 1 );

  newChar.kindred = json[ "kindred" ].get<int>();
  newChar.player  = json[ "player" ].get<int>();
  newChar.pass1   = json[ "pass1" ].get<unsigned int>();
  newChar.pass2   = json[ "pass2" ].get<unsigned int>();
  newChar.sprite  = json[ "sprite" ].get<unsigned int>();
  newChar.sound   = json[ "sound" ].get<unsigned int>();

  // clang-format off
  if (json[ "flags" ][ "immortal" ]               .get<bool>()) { newChar.flags |= CF_IMMORTAL;}
  if (json[ "flags" ][ "god" ]                    .get<bool>()) { newChar.flags |= CF_GOD;}
  if (json[ "flags" ][ "creator" ]                .get<bool>()) { newChar.flags |= CF_CREATOR;}
  if (json[ "flags" ][ "build_mode" ]             .get<bool>()) { newChar.flags |= CF_BUILDMODE;}
  if (json[ "flags" ][ "respawn" ]                .get<bool>()) { newChar.flags |= CF_RESPAWN;}
  if (json[ "flags" ][ "player" ]                 .get<bool>()) { newChar.flags |= CF_PLAYER;}
  if (json[ "flags" ][ "new_user" ]               .get<bool>()) { newChar.flags |= CF_NEWUSER;}
  if (json[ "flags" ][ "no_tell" ]                .get<bool>()) { newChar.flags |= CF_NOTELL;}
  if (json[ "flags" ][ "no_shout" ]               .get<bool>()) { newChar.flags |= CF_NOSHOUT;}
  if (json[ "flags" ][ "merchant" ]               .get<bool>()) { newChar.flags |= CF_MERCHANT;}
  if (json[ "flags" ][ "staff" ]                  .get<bool>()) { newChar.flags |= CF_STAFF;}
  if (json[ "flags" ][ "no_hp_regen" ]            .get<bool>()) { newChar.flags |= CF_NOHPREG;}
  if (json[ "flags" ][ "no_end_regen" ]           .get<bool>()) { newChar.flags |= CF_NOENDREG;}
  if (json[ "flags" ][ "no_mana_regen" ]          .get<bool>()) { newChar.flags |= CF_NOMANAREG;}
  if (json[ "flags" ][ "invisible" ]              .get<bool>()) { newChar.flags |= CF_INVISIBLE;}
  if (json[ "flags" ][ "infrared" ]               .get<bool>()) { newChar.flags |= CF_INFRARED;}
  if (json[ "flags" ][ "body" ]                   .get<bool>()) { newChar.flags |= CF_BODY;}
  if (json[ "flags" ][ "no_sleep" ]               .get<bool>()) { newChar.flags |= CF_NOSLEEP;}
  if (json[ "flags" ][ "undead" ]                 .get<bool>()) { newChar.flags |= CF_UNDEAD;}
  if (json[ "flags" ][ "no_magic" ]               .get<bool>()) { newChar.flags |= CF_NOMAGIC;}
  if (json[ "flags" ][ "stoned" ]                 .get<bool>()) { newChar.flags |= CF_STONED;}
  if (json[ "flags" ][ "usurp" ]                  .get<bool>()) { newChar.flags |= CF_USURP;}
  if (json[ "flags" ][ "imp" ]                    .get<bool>()) { newChar.flags |= CF_IMP;}
  if (json[ "flags" ][ "shutup" ]                 .get<bool>()) { newChar.flags |= CF_SHUTUP;}
  if (json[ "flags" ][ "no_description" ]         .get<bool>()) { newChar.flags |= CF_NODESC;}
  if (json[ "flags" ][ "profiler" ]               .get<bool>()) { newChar.flags |= CF_PROF;}
  if (json[ "flags" ][ "simple_anim" ]            .get<bool>()) { newChar.flags |= CF_SIMPLE;}
  if (json[ "flags" ][ "kicked" ]                 .get<bool>()) { newChar.flags |= CF_KICKED;}
  if (json[ "flags" ][ "no_list" ]                .get<bool>()) { newChar.flags |= CF_NOLIST;}
  if (json[ "flags" ][ "no_who" ]                 .get<bool>()) { newChar.flags |= CF_NOWHO;}
  if (json[ "flags" ][ "spell_ignore" ]           .get<bool>()) { newChar.flags |= CF_SPELLIGNORE;}
  if (json[ "flags" ][ "computer_controlled" ]    .get<bool>()) { newChar.flags |= CF_CCP;}
  if (json[ "flags" ][ "safe" ]                   .get<bool>()) { newChar.flags |= CF_SAFE;}
  if (json[ "flags" ][ "no_staff" ]               .get<bool>()) { newChar.flags |= CF_NOSTAFF;}
  if (json[ "flags" ][ "purple_of_honor" ]        .get<bool>()) { newChar.flags |= CF_POH;}
  if (json[ "flags" ][ "purple_of_honor_leader" ] .get<bool>()) { newChar.flags |= CF_POH_LEADER;}
  if (json[ "flags" ][ "thrall" ]                 .get<bool>()) { newChar.flags |= CF_THRALL;}
  if (json[ "flags" ][ "lab_keeper" ]             .get<bool>()) { newChar.flags |= CF_LABKEEPER;}
  if (json[ "flags" ][ "is_looting" ]             .get<bool>()) { newChar.flags |= CF_ISLOOTING;}
  if (json[ "flags" ][ "golden" ]                 .get<bool>()) { newChar.flags |= CF_GOLDEN;}
  if (json[ "flags" ][ "black" ]                  .get<bool>()) { newChar.flags |= CF_BLACK;}
  if (json[ "flags" ][ "password" ]               .get<bool>()) { newChar.flags |= CF_PASSWD;}
  if (json[ "flags" ][ "update" ]                 .get<bool>()) { newChar.flags |= CF_UPDATE;}
  if (json[ "flags" ][ "save_me" ]                .get<bool>()) { newChar.flags |= CF_SAVEME;}
  if (json[ "flags" ][ "greater_god" ]            .get<bool>()) { newChar.flags |= CF_GREATERGOD;}
  if (json[ "flags" ][ "greater_invisibility" ]   .get<bool>()) { newChar.flags |= CF_GREATERINV;}
  // clang-format on

  newChar.alignment = json[ "alignment" ].get<int>();
  newChar.temple_x  = json[ "temple_x" ].get<unsigned int>();
  newChar.temple_y  = json[ "temple_y" ].get<unsigned int>();
  newChar.tavern_x  = json[ "tavern_x" ].get<unsigned int>();
  newChar.tavern_y  = json[ "tavern_y" ].get<unsigned int>();
  newChar.temp      = json[ "temp" ].get<unsigned int>();

  const nlohmann::json& jsonAttributes = json[ "attributes" ];
  for ( int i = 0; i < 5; ++i )
  {
    for ( int j = 0; j < 6; ++j )
    {
      newChar.attrib[ i ][ j ] = jsonAttributes[ i ][ "data" ][ j ].get<unsigned int>();
    }
  }

  for ( int i = 0; i < 6; ++i )
  {
    newChar.hp[ i ]   = json[ "hp" ][ i ].get<unsigned int>();
    newChar.end[ i ]  = json[ "end" ][ i ].get<unsigned int>();
    newChar.mana[ i ] = json[ "mana" ][ i ].get<unsigned int>();
  }

  const nlohmann::json& jsonSkills = json[ "skills" ];
  for ( int i = 0; i < 50; ++i )
  {
    for ( int j = 0; j < 6; ++j )
    {
      newChar.skill[ i ][ j ] = jsonSkills[ i ][ "data" ][ j ].get<unsigned int>();
    }
  }

  newChar.weapon_bonus = json[ "weapon_bonus" ].get<unsigned int>();
  newChar.armor_bonus  = json[ "armor_bonus" ].get<unsigned int>();
  newChar.a_hp         = json[ "a_hp" ].get<int>();
  newChar.a_end        = json[ "a_end" ].get<int>();
  newChar.a_mana       = json[ "a_mana" ].get<int>();
  newChar.light        = json[ "light" ].get<unsigned int>();
  newChar.mode         = json[ "mode" ].get<unsigned int>();
  newChar.speed        = json[ "speed" ].get<int>();
  newChar.points       = json[ "points" ].get<int>();
  newChar.points_tot   = json[ "points_tot" ].get<int>();
  newChar.armor        = json[ "armor" ].get<int>();
  newChar.weapon       = json[ "weapon" ].get<int>();
  newChar.x            = json[ "x" ].get<int>();
  newChar.y            = json[ "y" ].get<int>();
  newChar.tox          = json[ "tox" ].get<int>();
  newChar.toy          = json[ "toy" ].get<int>();
  newChar.frx          = json[ "frx" ].get<int>();
  newChar.fry          = json[ "fry" ].get<int>();
  newChar.status       = json[ "status" ].get<int>();
  newChar.status2      = json[ "status2" ].get<int>();
  newChar.dir          = json[ "dir" ].get<unsigned int>();
  newChar.gold         = json[ "gold" ].get<int>();

  for ( int i = 0; i < 40; ++i )
  {
    newChar.item[ i ] = json[ "item" ][ i ].get<unsigned int>();
  }

  for ( int i = 0; i < 20; ++i )
  {
    newChar.worn[ i ]  = json[ "worn" ][ i ].get<unsigned int>();
    newChar.spell[ i ] = json[ "spell" ][ i ].get<unsigned int>();
  }

  newChar.citem               = json[ "citem" ].get<unsigned int>();
  newChar.creation_date       = json[ "creation_date" ].get<unsigned int>();
  newChar.login_date          = json[ "login_date" ].get<unsigned int>();
  newChar.addr                = json[ "addr" ].get<unsigned int>();
  newChar.current_online_time = json[ "current_online_time" ].get<unsigned int>();
  newChar.total_online_time   = json[ "total_online_time" ].get<unsigned int>();
  newChar.comp_volume         = json[ "comp_volume" ].get<unsigned int>();
  newChar.raw_volume          = json[ "raw_volume" ].get<unsigned int>();
  newChar.idle                = json[ "idle" ].get<unsigned int>();
  newChar.attack_cn           = json[ "attack_cn" ].get<unsigned int>();
  newChar.skill_nr            = json[ "skill_nr" ].get<unsigned int>();
  newChar.skill_target1       = json[ "skill_target1" ].get<unsigned int>();
  newChar.skill_target2       = json[ "skill_target2" ].get<unsigned int>();
  newChar.goto_x              = json[ "goto_x" ].get<unsigned int>();
  newChar.goto_y              = json[ "goto_y" ].get<unsigned int>();
  newChar.use_nr              = json[ "use_nr" ].get<unsigned int>();
  newChar.misc_action         = json[ "misc_action" ].get<unsigned int>();
  newChar.misc_target1        = json[ "misc_target1" ].get<unsigned int>();
  newChar.misc_target2        = json[ "misc_target2" ].get<unsigned int>();
  newChar.cerrno              = json[ "cerrno" ].get<unsigned int>();
  newChar.escape_timer        = json[ "escape_timer" ].get<unsigned int>();

  for ( int i = 0; i < 4; ++i )
  {
    newChar.enemy[ i ] = json[ "enemy" ][ i ].get<unsigned int>();
  }

  newChar.current_enemy = json[ "current_enemy" ].get<unsigned int>();
  newChar.retry         = json[ "retry" ].get<unsigned int>();
  newChar.stunned       = json[ "stunned" ].get<unsigned int>();
  newChar.speed_mod     = json[ "speed_mode" ].get<int>();
  newChar.last_action   = json[ "last_action" ].get<int>();
  newChar.unused        = json[ "unused" ].get<int>();
  newChar.depot_sold    = json[ "depot_sold" ].get<int>();
  newChar.gethit_dam    = json[ "gethit_dam" ].get<int>();
  newChar.gethit_bonus  = json[ "gethit_bonus" ].get<int>();
  newChar.light_bonus   = json[ "light_bonus" ].get<unsigned int>();

  std::strncpy( newChar.passwd, json[ "password" ].get<std::string>().c_str(), sizeof( newChar.passwd ) - 1 );

  newChar.lastattack = json[ "lastattack" ].get<int>();

  for ( int i = 0; i < 25; ++i )
  {
    newChar.future1[ i ] = json[ "future1" ][ i ].get<int>();
  }

  for ( int i = 0; i < 49; ++i )
  {
    newChar.future2[ i ] = json[ "future2" ][ i ].get<int>();
  }

  for ( int i = 0; i < 62; ++i )
  {
    newChar.depot[ i ] = json[ "depot" ][ i ].get<unsigned int>();
  }

  for ( int i = 0; i < 12; ++i )
  {
    newChar.future3[ i ] = json[ "future3" ][ i ].get<int>();
  }

  for ( int i = 0; i < 100; ++i )
  {
    newChar.data[ i ] = json[ "data" ][ i ].get<int>();
  }

  for ( int i = 0; i < 10; ++i )
  {
    std::strncpy( newChar.text[ i ], json[ "text" ][ i ].get<std::string>().c_str(), sizeof( newChar.text[ i ] ) - 1 );
  }

  newChar.sprite_override = json[ "sprite_override" ].get<int>();
  newChar.depot_cost      = json[ "depot_cost" ].get<int>();
  newChar.luck            = json[ "luck" ].get<int>();
  newChar.unreach         = json[ "unreach" ].get<int>();
  newChar.unreachx        = json[ "unreach_x" ].get<int>();
  newChar.unreachy        = json[ "unreach_y" ].get<int>();
  newChar.monsterClass    = json[ "monsterClass" ].get<int>();

  return newChar;
}

nlohmann::json character::toJson() const
{
  nlohmann::json root {};

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
  //root[ "flags" ]                             = Json::objectValue;
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

  // //root[ "attributes" ]                        = Json::arrayValue;
  // std::array< const char*, 5 > attributeNames = { "Braveness", "Willpower", "Intuition", "Agility", "Strength" };
  // for ( int i = 0; i < 5; ++i )
  // {
  //   nlohmann::json attributeRoot {};
  //   attributeRoot[ "name" ] = attributeNames[ i ];
  //   //attributeRoot[ "data" ] = Json::arrayValue;
  //   for ( int j = 0; j < 6; ++j )
  //   {
  //     attributeRoot[ "data" ].append( attrib[ i ][ j ] );
  //   }

  //   root[ "attributes" ].append( attributeRoot );
  // }

  //root[ "hp" ]   = Json::arrayValue;
  //root[ "end" ]  = Json::arrayValue;
  //root[ "mana" ] = Json::arrayValue;

  for ( int i = 0; i < 6; ++i )
  {
    root[ "hp" ][ i ]   = hp[ i ];
    root[ "end" ][ i ]  = end[ i ];
    root[ "mana" ][ i ] = mana[ i ];
  }

  //root[ "skills" ] = Json::arrayValue;
  // for ( int i = 0; i < 50; ++i )
  // {
  //   nlohmann::json skillRoot {};

  //   if ( std::string( static_skilltab[ i ].name ).empty() )
  //   {
  //     continue;
  //   }

  //   skillRoot[ "name" ] = static_skilltab[ i ].name;
  //   //skillRoot[ "data" ] = Json::arrayValue;
  //   for ( int j = 0; j < 6; ++j )
  //   {
  //     skillRoot[ "data" ].append( skill[ i ][ j ] );
  //   }

  //   root[ "skills" ].append( skillRoot );
  // }

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

  //root[ "item" ] = Json::arrayValue;
  for ( int i = 0; i < 40; ++i )
  {
    root[ "item" ][ i ] = item[ i ];
  }

  //root[ "worn" ]  = Json::arrayValue;
  //root[ "spell" ] = Json::arrayValue;
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

  //root[ "enemy" ] = Json::arrayValue;
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

  //root[ "future1" ] = Json::arrayValue;
  //root[ "future2" ] = Json::arrayValue;
  //root[ "depot" ]   = Json::arrayValue;
  //root[ "future3" ] = Json::arrayValue;
  //root[ "data" ]    = Json::arrayValue;
  //root[ "text" ]    = Json::arrayValue;

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

void character::setTotalExperienceFromSkillsAndAttributes()
{
  std::int32_t expTotal {};

  if ( points_tot != 0 )
  {
    std::cerr << "Re-setting experience when points_total is NOT 0!" << std::endl;
  }

  for ( int z = 0; z < 5; z++ )
  { // 10 is the starting value at this point
    for ( int m = 10; m < this->attrib[ z ][ 0 ]; m++ )
    {
      expTotal += attrib_needed( m, attrib[ z ][ 2 ], attrib[ z ][ 3 ] );
    }
  }

  for ( int m = 50; m < hp[ 0 ]; m++ )
  {
    expTotal += hp_needed( m, hp[ 2 ], hp[ 3 ] );
  }

  for ( int m = 50; m < end[ 0 ]; m++ )
  {
    expTotal += end_needed( m, end[ 2 ], end[ 3 ] );
  }

  for ( int m = 50; m < mana[ 0 ]; m++ )
  {
    expTotal += mana_needed( m, mana[ 2 ], mana[ 3 ] );
  }

  for ( int z = 0; z < 50; z++ )
  {
    for ( int m = 1; m < skill[ z ][ 0 ]; m++ )
    {
      expTotal += skill_needed( m, skill[ z ][ 2 ], skill[ z ][ 3 ] );
    }
  }
}