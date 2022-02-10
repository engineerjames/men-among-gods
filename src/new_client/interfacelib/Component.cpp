#include "Component.h"

namespace MenAmongGods
{

Component::Component()
    : sf::Drawable()
    , commands_()
{
}

void Component::populateCommands( std::vector< std::shared_ptr< ClientCommand > >& outCommands )
{
  // Insert our commands into the end of the command list passed in
  outCommands.insert( std::end( outCommands ), std::begin( commands_ ), std::end( commands_ ) );

  // To ensure we don't keep re-inserting the same commands, clear our internal command list.
  commands_.clear();
}

} // namespace MenAmongGods