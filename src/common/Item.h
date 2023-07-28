#ifndef MEN_AMONG_GODS_ITEM_H
#define MEN_AMONG_GODS_ITEM_H

#include <cstdint>

#include <nlohmann/json.hpp>

#pragma pack( push, 1 )
struct item
{
  std::uint8_t used;               // 1
  char         name[ 40 ];         // 41
  char         reference[ 40 ];    // 81, a pair of boots
  char         description[ 200 ]; // 281, A pair of studded leather boots.

  unsigned long long flags; // 289, s.a.

  std::uint32_t value;     // 293, value to a merchant
  std::uint16_t placement; // 295, see constants above

  std::uint16_t temp; // 297, created from template temp

  unsigned char damage_state; // 298, has reached damage level X of 5, 0=OK, 4=almost destroyed, 5=destroyed

  // states for non-active [0] and active[1]
  std::uint32_t max_age[ 2 ];     // 306, maximum age per state
  std::uint32_t current_age[ 2 ]; // 314, current age in current state

  std::uint32_t max_damage;     // 318, maximum damage per state
  std::uint32_t current_damage; // 322, current damage in current state

  // modifiers - modifiers apply only when the item is being
  // worn (wearable objects) or when spell is cast. After duration expires,
  // the effects are removed.

  // modifiers - modifier [0] applies when the item is being
  // worn (wearable objects) or is added to the powers (spells) for permanent spells
  // modifier [1] applies when it is active
  // modifier [2] is not a modifier but the minimum value that attibute/skill must have to wear or use
  // the item

  char attrib[ 5 ][ 3 ]; // 337

  std::int16_t hp[ 3 ];   // 343
  std::int16_t end[ 3 ];  // 349
  std::int16_t mana[ 3 ]; // 355

  char skill[ 50 ][ 3 ]; // 505

  char armor[ 2 ];  // 506
  char weapon[ 2 ]; // 507

  std::int16_t light[ 2 ]; // 511

  std::uint32_t duration; // 515
  std::uint32_t cost;     // 519
  std::uint32_t power;    // 523
  std::uint32_t active;   // 527

  // map stuff
  std::uint16_t x, y;            // 531, current position        NOTE: x=0, y=0 = void
  std::uint16_t carried;         // 533, carried by character carried
  std::uint16_t sprite_override; // 535, used for potions/spells which change the character sprite

  std::int16_t  sprite[ 2 ]; // 543
  unsigned char status[ 2 ]; // 545

  char gethit_dam[ 2 ]; // 547, damage for hitting this item

  char min_rank; // minimum rank to wear the item
  char future[ 3 ];
  int  future3[ 9 ]; // 587

  int t_bought; // 591
  int t_sold;   // 595

  unsigned char driver;     // 596, special routines for LOOKSPECIAL and USESPECIAL
  std::uint32_t data[ 10 ]; // 634, driver data

  nlohmann::json toJson() const;
  static item fromJson( const nlohmann::json& json );
};
#pragma pack( pop )
static_assert( sizeof( item ) == 634 );

#endif