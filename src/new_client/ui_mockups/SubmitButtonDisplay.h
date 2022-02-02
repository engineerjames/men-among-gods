#ifndef MEN_AMONG_GODS_SUBMIT_BUTTON_DISPLAY_H
#define MEN_AMONG_GODS_SUBMIT_BUTTON_DISPLAY_H

#include "Component.h"

#include <SFML/Graphics.hpp>

#include <functional>

namespace MenAmongGods
{
class SubmitButtonDisplay : public MenAmongGods::Component
{
public:
  SubmitButtonDisplay( const sf::RenderWindow& window, const sf::Font& font, unsigned int fontSize, sf::Vector2f buttonSize );
  virtual ~SubmitButtonDisplay() = default;

  void setPosition( const sf::Vector2f& newPosition );

  // Component interface
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  void setCallBack( std::function< void() > callBack );

  // sf::Drawable interface
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  const sf::RenderWindow& window_;
  sf::RectangleShape      buttonShape_;
  sf::Text                buttonText_;
  std::function< void() > submitCallback_;
  bool                    isActivated_;
  bool                    isEnabled_;
};
} // namespace MenAmongGods

#endif