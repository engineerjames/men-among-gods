#include "Component.h"

namespace MenAmongGods
{

Component::Component()
    : sf::Drawable()
{
}

std::vector< std::unique_ptr< ClientCommand > > Component::getCommands() const
{
  // Default behavior is to do nothing
  return std::vector< std::unique_ptr< ClientCommand > > {};
}
} // namespace MenAmongGods