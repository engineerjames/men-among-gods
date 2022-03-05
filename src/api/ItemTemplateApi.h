#ifndef MEN_AMONG_GODS_ITEM_TEMPLATE_API
#define MEN_AMONG_GODS_ITEM_TEMPLATE_API

#include <drogon/HttpController.h>
#include <vector>

namespace api
{
namespace v1
{
#pragma pack( push, 1 )
struct item
{
  unsigned char used;               // 1
  char          name[ 40 ];         // 41
  char          reference[ 40 ];    // 81, a pair of boots
  char          description[ 200 ]; // 281, A pair of studded leather boots.

  unsigned long long flags; // 289, s.a.

  unsigned int   value;     // 293, value to a merchant
  unsigned short placement; // 295, see constants above

  unsigned short temp; // 297, created from template temp

  unsigned char damage_state; // 298, has reached damage level X of 5, 0=OK, 4=almost destroyed, 5=destroyed

  // states for non-active [0] and active[1]
  unsigned int max_age[ 2 ];     // 306, maximum age per state
  unsigned int current_age[ 2 ]; // 314, current age in current state

  unsigned int max_damage;     // 318, maximum damage per state
  unsigned int current_damage; // 322, current damage in current state

  // modifiers - modifiers apply only when the item is being
  // worn (wearable objects) or when spell is cast. After duration expires,
  // the effects are removed.

  // modifiers - modifier [0] applies when the item is being
  // worn (wearable objects) or is added to the powers (spells) for permanent spells
  // modifier [1] applies when it is active
  // modifier [2] is not a modifier but the minimum value that attibute/skill must have to wear or use
  // the item

  char attrib[ 5 ][ 3 ]; // 337

  short hp[ 3 ];   // 343
  short end[ 3 ];  // 349
  short mana[ 3 ]; // 355

  char skill[ 50 ][ 3 ]; // 505

  char armor[ 2 ];  // 506
  char weapon[ 2 ]; // 507

  short light[ 2 ]; // 511

  unsigned int duration; // 515
  unsigned int cost;     // 519
  unsigned int power;    // 523
  unsigned int active;   // 527

  // map stuff
  unsigned short int x, y;            // 531, current position        NOTE: x=0, y=0 = void
  unsigned short     carried;         // 533, carried by character carried
  unsigned short     sprite_override; // 535, used for potions/spells which change the character sprite

  short int     sprite[ 2 ]; // 543
  unsigned char status[ 2 ]; // 545

  char gethit_dam[ 2 ]; // 547, damage for hitting this item

  char min_rank; // minimum rank to wear the item
  char future[ 3 ];
  int  future3[ 9 ]; // 587

  int t_bought; // 591
  int t_sold;   // 595

  unsigned char driver;     // 596, special routines for LOOKSPECIAL and USESPECIAL
  unsigned int  data[ 10 ]; // 634, driver data
};
#pragma pack( pop )

class ItemTemplateApi : public drogon::HttpController< ItemTemplateApi >
{
public:
  METHOD_LIST_BEGIN
  METHOD_ADD( ItemTemplateApi::getItemTemplates, "", drogon::Get );
  METHOD_LIST_END

  // your declaration of processing function maybe like this:
  void getItemTemplates( const drogon::HttpRequestPtr& req, std::function< void( const drogon::HttpResponsePtr& ) >&& callback ) const;

  ItemTemplateApi();

private:
  std::vector< item > itemTemplates_;
};
} // namespace v1
} // namespace api

#endif