#include "item.h"
#include <json/json.h>

#include <cstdint>

item item::fromJson( const Json::Value& json )
{
  item newItem {};

  newItem.used = json[ "used" ].asInt();

  std::strncpy( newItem.name, json[ "name" ].asString().c_str(), sizeof( newItem.name ) - 1 );
  std::strncpy( newItem.reference, json[ "reference" ].asString().c_str(), sizeof( newItem.reference ) - 1 );
  std::strncpy( newItem.description, json[ "description" ].asString().c_str(), sizeof( newItem.description ) - 1 );

  newItem.value        = json[ "value" ].asUInt();
  newItem.placement    = json[ "placement" ].asUInt();
  newItem.temp         = json[ "temp" ].asUInt();
  newItem.damage_state = json[ "damage_state" ].asUInt();

  newItem.max_age[ 0 ] = json[ "max_age" ][ 0 ].asUInt();
  newItem.max_age[ 1 ] = json[ "max_age" ][ 1 ].asUInt();

  newItem.current_age[ 0 ] = json[ "current_age" ][ 0 ].asUInt();
  newItem.current_age[ 1 ] = json[ "current_age" ][ 1 ].asUInt();
  newItem.current_damage   = json[ "current_damage" ].asUInt();
  newItem.max_damage       = json[ "max_damage" ].asUInt();

  for ( int i = 0; i < 3; ++i )
  {
    newItem.hp[ i ]   = json[ "hp" ][ i ].asUInt();
    newItem.end[ i ]  = json[ "end" ][ i ].asUInt();
    newItem.mana[ i ] = json[ "mana" ][ i ].asUInt();
  }

  for ( int i = 0; i < 2; ++i )
  {
    newItem.armor[ i ]      = json[ "armor" ][ i ].asInt();
    newItem.weapon[ i ]     = json[ "weapon" ][ i ].asInt();
    newItem.light[ i ]      = json[ "light" ][ i ].asInt();
    newItem.sprite[ i ]     = json[ "sprite" ][ i ].asInt();
    newItem.status[ i ]     = json[ "status" ][ i ].asUInt();
    newItem.gethit_dam[ i ] = json[ "gethit_dam" ][ i ].asInt();
  }

  newItem.duration        = json[ "duration" ].asUInt();
  newItem.cost            = json[ "cost" ].asUInt();
  newItem.power           = json[ "power" ].asUInt();
  newItem.active          = json[ "active" ].asUInt();
  newItem.x               = json[ "x" ].asUInt();
  newItem.y               = json[ "y" ].asUInt();
  newItem.carried         = json[ "carried" ].asUInt();
  newItem.sprite_override = json[ "sprite_override" ].asUInt();
  newItem.min_rank        = json[ "min_rank" ].asInt();

  for ( int i = 0; i < 3; ++i )
  {
    newItem.future[ i ] = json[ "future" ][ i ].asInt();
  }

  for ( int i = 0; i < 9; ++i )
  {
    newItem.future3[ i ] = json[ "future3" ][ i ].asInt();
  }

  newItem.t_bought = json[ "t_bought" ].asInt();
  newItem.t_sold   = json[ "t_sold" ].asInt();
  newItem.driver   = json[ "driver" ].asUInt();

  for ( int i = 0; i < 10; ++i )
  {
    newItem.data[ i ] = json[ "data" ][ i ].asUInt();
  }

  return newItem;
}

Json::Value item::toJson() const
{
  Json::Value root {};

  root[ "used" ]        = used;
  root[ "name" ]        = name;
  root[ "reference" ]   = reference;
  root[ "description" ] = description;

  root[ "value" ]        = value;
  root[ "placement" ]    = placement;
  root[ "temp" ]         = temp;
  root[ "damage_state" ] = damage_state;

  root[ "max_age" ]      = Json::arrayValue;
  root[ "max_age" ][ 0 ] = max_age[ 0 ];
  root[ "max_age" ][ 1 ] = max_age[ 1 ];

  root[ "current_age" ]      = Json::arrayValue;
  root[ "current_age" ][ 0 ] = current_age[ 0 ];
  root[ "current_age" ][ 1 ] = current_age[ 1 ];

  root[ "current_damage" ] = current_damage;
  root[ "max_damage" ]     = max_damage;

  root[ "hp" ]   = Json::arrayValue;
  root[ "end" ]  = Json::arrayValue;
  root[ "mana" ] = Json::arrayValue;

  for ( int i = 0; i < 3; ++i )
  {
    root[ "hp" ][ i ]   = hp[ i ];
    root[ "end" ][ i ]  = end[ i ];
    root[ "mana" ][ i ] = mana[ i ];
  }

  root[ "armor" ]      = Json::arrayValue;
  root[ "weapon" ]     = Json::arrayValue;
  root[ "light" ]      = Json::arrayValue;
  root[ "sprite" ]     = Json::arrayValue;
  root[ "status" ]     = Json::arrayValue;
  root[ "gethit_dam" ] = Json::arrayValue;

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

  root[ "future" ] = Json::arrayValue;
  for ( int i = 0; i < 3; ++i )
  {
    root[ "future" ][ i ] = future[ i ];
  }

  root[ "future3" ] = Json::arrayValue;
  for ( int i = 0; i < 9; ++i )
  {
    root[ "future3" ][ i ] = future3[ i ];
  }

  root[ "t_bought" ] = t_bought;
  root[ "t_sold" ]   = t_sold;
  root[ "driver" ]   = driver;

  root[ "data" ] = Json::arrayValue;

  for ( int i = 0; i < 10; ++i )
  {
    root[ "data" ][ i ] = data[ i ];
  }

  return root;
}
