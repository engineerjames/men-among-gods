#ifndef MEN_AMONG_GODS_COMPONENT_H
#define MEN_AMONG_GODS_COMPONENT_H

#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include <vector>

#include "ClientCommand.h"

namespace sf
{
class Event;
}

namespace MenAmongGods
{
class Component : public sf::Drawable
{
public:
  // Update is called *at least* once per frame--this means individual components
  // are responsible for controlling the behavior if *only* once per frame is needed.
  // See Map's implementation for an example. REWORD THIS COMMENT
  virtual void update() = 0;

  virtual void onUserInput( const sf::Event& e ) = 0;

  // Finalize is called once at the end of every frame
  virtual void finalize() = 0;

  // Grab commands to send to our networking thread
  virtual std::vector< std::unique_ptr< ClientCommand > > getCommands() const;

  Component();
  Component( const Component& ) = default;
  Component& operator=( const Component& ) = default;

  virtual ~Component() = default;
};
} // namespace MenAmongGods

#endif