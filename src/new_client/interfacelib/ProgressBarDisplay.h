#ifndef MEN_AMONG_GODS_PROGRESS_BAR_DISPLAY_H
#define MEN_AMONG_GODS_PROGRESS_BAR_DISPLAY_H

#include "Component.h"

#include <SFML/Graphics.hpp>

namespace MenAmongGods
{
class ProgressBarDisplay : public MenAmongGods::Component
{
public:
  ProgressBarDisplay( const sf::Vector2f& size );
  virtual ~ProgressBarDisplay() = default;

  // Component interface
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  // sf::Drawable interface
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  void setPercentComplete( float percentComplete );
  bool isComplete() const;
  void setActive( bool isActive );

  void setPosition( const sf::Vector2f& newPosition );

private:
  sf::RectangleShape backgroundRect_;
  sf::RectangleShape foregroundRect_;
  float              percentComplete_;
  bool               isActive_;
};
} // namespace MenAmongGods

#endif