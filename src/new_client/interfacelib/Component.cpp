#include "Component.h"

namespace MenAmongGods
{

Component::Component()
    : sf::Drawable()
    , commands_()
{
}

const std::vector< std::shared_ptr< ClientCommand > >& Component::getCommands() const
{
  return commands_;
}

void Component::clearCommands()
{
  commands_.clear();
}
} // namespace MenAmongGods