#ifndef MEN_AMONG_GODS_COMPONENT_H
#define MEN_AMONG_GODS_COMPONENT_H

namespace sf
{
class Event;
}

namespace MenAmongGods
{
class Component
{
public:
  // Update is called *at least* once per frame--this means individual components
  // are responsible for controlling the behavior if *only* once per frame is needed.
  // See Map's implementation for an example. REWORD THIS COMMENT
  virtual void update() = 0;

  virtual void onUserInput( const sf::Event& e ) = 0;

  // Finalize is called once at the end of every frame
  virtual void finalize() = 0;

  virtual ~Component() = default;
};
} // namespace MenAmongGods

#endif