#ifndef MEN_AMONG_GODS_RADIO_BUTTON_DISPLAY_H
#define MEN_AMONG_GODS_RADIO_BUTTON_DISPLAY_H

#include "Component.h"

#include <SFML/Graphics.hpp>

#include <string>

namespace MenAmongGods
{
class RadioButtonDisplay : public MenAmongGods::Component
{
public:
  RadioButtonDisplay( const sf::RenderWindow& window, const sf::Font& font, const std::string& labelText, float circleRadius,
                      unsigned int fontSize );
  ~RadioButtonDisplay() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  void setPosition( const sf::Vector2f& newPosition );
  bool isSelected() const;

private:
  const sf::RenderWindow& window_;
  sf::CircleShape         outerCircle_;
  sf::CircleShape         innerCircle_;
  bool                    isSelected_;
  sf::Text                labelText_;
};
} // namespace MenAmongGods

#endif