#include "item.h"
#include <json/json.h>

#include <cstdint>

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

  root[ "future" ]  = future;
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
