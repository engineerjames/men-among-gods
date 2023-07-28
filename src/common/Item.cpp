#include "Item.h"

#include <nlohmann/json.hpp>

item item::fromJson( const nlohmann::json& json )
{
  item newItem {};

  newItem.used = json[ "used" ].get<int>();

  std::strncpy( newItem.name, json[ "name" ].get<std::string>().c_str(), sizeof( newItem.name ) - 1 );
  std::strncpy( newItem.reference, json[ "reference" ].get<std::string>().c_str(), sizeof( newItem.reference ) - 1 );
  std::strncpy( newItem.description, json[ "description" ].get<std::string>().c_str(), sizeof( newItem.description ) - 1 );

  newItem.value        = json[ "value" ].get<unsigned int>();
  newItem.placement    = json[ "placement" ].get<unsigned int>();
  newItem.temp         = json[ "temp" ].get<unsigned int>();
  newItem.damage_state = json[ "damage_state" ].get<unsigned int>();

  newItem.max_age[ 0 ] = json[ "max_age" ][ 0 ].get<unsigned int>();
  newItem.max_age[ 1 ] = json[ "max_age" ][ 1 ].get<unsigned int>();

  newItem.current_age[ 0 ] = json[ "current_age" ][ 0 ].get<unsigned int>();
  newItem.current_age[ 1 ] = json[ "current_age" ][ 1 ].get<unsigned int>();
  newItem.current_damage   = json[ "current_damage" ].get<unsigned int>();
  newItem.max_damage       = json[ "max_damage" ].get<unsigned int>();

  for ( int i = 0; i < 3; ++i )
  {
    newItem.hp[ i ]   = json[ "hp" ][ i ].get<unsigned int>();
    newItem.end[ i ]  = json[ "end" ][ i ].get<unsigned int>();
    newItem.mana[ i ] = json[ "mana" ][ i ].get<unsigned int>();
  }

  for ( int i = 0; i < 2; ++i )
  {
    newItem.armor[ i ]      = json[ "armor" ][ i ].get<int>();
    newItem.weapon[ i ]     = json[ "weapon" ][ i ].get<int>();
    newItem.light[ i ]      = json[ "light" ][ i ].get<int>();
    newItem.sprite[ i ]     = json[ "sprite" ][ i ].get<int>();
    newItem.status[ i ]     = json[ "status" ][ i ].get<unsigned int>();
    newItem.gethit_dam[ i ] = json[ "gethit_dam" ][ i ].get<int>();
  }

  newItem.duration        = json[ "duration" ].get<unsigned int>();
  newItem.cost            = json[ "cost" ].get<unsigned int>();
  newItem.power           = json[ "power" ].get<unsigned int>();
  newItem.active          = json[ "active" ].get<unsigned int>();
  newItem.x               = json[ "x" ].get<unsigned int>();
  newItem.y               = json[ "y" ].get<unsigned int>();
  newItem.carried         = json[ "carried" ].get<unsigned int>();
  newItem.sprite_override = json[ "sprite_override" ].get<unsigned int>();
  newItem.min_rank        = json[ "min_rank" ].get<int>();

  for ( int i = 0; i < 3; ++i )
  {
    newItem.future[ i ] = json[ "future" ][ i ].get<int>();
  }

  for ( int i = 0; i < 9; ++i )
  {
    newItem.future3[ i ] = json[ "future3" ][ i ].get<int>();
  }

  newItem.t_bought = json[ "t_bought" ].get<int>();
  newItem.t_sold   = json[ "t_sold" ].get<int>();
  newItem.driver   = json[ "driver" ].get<unsigned int>();

  for ( int i = 0; i < 10; ++i )
  {
    newItem.data[ i ] = json[ "data" ][ i ].get<unsigned int>();
  }

  return newItem;
}

nlohmann::json item::toJson() const
{
  nlohmann::json root {};

  root[ "used" ]        = used;
  root[ "name" ]        = name;
  root[ "reference" ]   = reference;
  root[ "description" ] = description;

  root[ "value" ]        = value;
  root[ "placement" ]    = placement;
  root[ "temp" ]         = temp;
  root[ "damage_state" ] = damage_state;

  //root[ "max_age" ]      = Json::arrayValue;
  root[ "max_age" ][ 0 ] = max_age[ 0 ];
  root[ "max_age" ][ 1 ] = max_age[ 1 ];

  //root[ "current_age" ]      = Json::arrayValue;
  root[ "current_age" ][ 0 ] = current_age[ 0 ];
  root[ "current_age" ][ 1 ] = current_age[ 1 ];

  root[ "current_damage" ] = current_damage;
  root[ "max_damage" ]     = max_damage;

  //root[ "hp" ]   = Json::arrayValue;
  //root[ "end" ]  = Json::arrayValue;
  //root[ "mana" ] = Json::arrayValue;

  for ( int i = 0; i < 3; ++i )
  {
    root[ "hp" ][ i ]   = hp[ i ];
    root[ "end" ][ i ]  = end[ i ];
    root[ "mana" ][ i ] = mana[ i ];
  }

  //root[ "armor" ]      = Json::arrayValue;
  //root[ "weapon" ]     = Json::arrayValue;
  //root[ "light" ]      = Json::arrayValue;
  //root[ "sprite" ]     = Json::arrayValue;
  //root[ "status" ]     = Json::arrayValue;
  //root[ "gethit_dam" ] = Json::arrayValue;

  for ( int i = 0; i < 2; ++i )
  {
    root[ "armor" ][ i ]      = armor[ i ];
    root[ "weapon" ][ i ]     = weapon[ i ];
    root[ "light" ][ i ]      = light[ i ];
    root[ "sprite" ][ i ]     = sprite[ i ];
    root[ "status" ][ i ]     = status[ i ];
    root[ "gethit_dam" ][ i ] = gethit_dam[ i ];
  }

  root[ "duration" ]        = duration;
  root[ "cost" ]            = cost;
  root[ "power" ]           = power;
  root[ "active" ]          = active;
  root[ "x" ]               = x;
  root[ "y" ]               = y;
  root[ "carried" ]         = carried;
  root[ "sprite_override" ] = sprite_override;
  root[ "min_rank" ]        = min_rank;

  //root[ "future" ] = Json::arrayValue;
  for ( int i = 0; i < 3; ++i )
  {
    root[ "future" ][ i ] = future[ i ];
  }

  //root[ "future3" ] = Json::arrayValue;
  for ( int i = 0; i < 9; ++i )
  {
    root[ "future3" ][ i ] = future3[ i ];
  }

  root[ "t_bought" ] = t_bought;
  root[ "t_sold" ]   = t_sold;
  root[ "driver" ]   = driver;

  //root[ "data" ] = Json::arrayValue;

  for ( int i = 0; i < 10; ++i )
  {
    root[ "data" ][ i ] = data[ i ];
  }

  return root;
}
