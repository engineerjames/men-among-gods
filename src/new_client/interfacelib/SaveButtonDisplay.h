#ifndef MEN_AMONG_GODS_SAVE_BUTTON_DISPLAY_H
#define MEN_AMONG_GODS_SAVE_BUTTON_DISPLAY_H

#include "Component.h"

#include <SFML/Graphics.hpp>

class PlayerData;

namespace MenAmongGods
{
class SaveButtonDisplay : public MenAmongGods::Component
{
public:
  SaveButtonDisplay( const sf::RenderWindow& window, const PlayerData& playerData, const sf::Font& font, const unsigned int fontSize,
                     sf::Vector2f buttonSize );
  virtual ~SaveButtonDisplay() = default;

  void setPosition( const sf::Vector2f& newPosition );

  // Component interface
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  // sf::Drawable interface
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  const sf::RenderWindow& window_;
  const PlayerData&       playerData_;
  sf::RectangleShape      buttonShape_;
  sf::Text                buttonText_;
};
} // namespace MenAmongGods

#endif