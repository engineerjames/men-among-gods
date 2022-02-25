#ifndef MEN_AMONG_GODS_NEW_BUTTON_DISPLAY_H
#define MEN_AMONG_GODS_NEW_BUTTON_DISPLAY_H

#include "Component.h"

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <functional>

class PlayerData;

namespace MenAmongGods
{
class NewButtonDisplay : public MenAmongGods::Component
{
public:
  NewButtonDisplay( const sf::RenderWindow& window, PlayerData& playerData, const sf::Font& font, const unsigned int fontSize,
                    sf::Vector2f buttonSize );
  virtual ~NewButtonDisplay() = default;

  void setPosition( const sf::Vector2f& newPosition );

  // Component interface
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  // sf::Drawable interface
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  void setCallBack( std::function< void() > callBack );

private:
  const sf::RenderWindow& window_;
  PlayerData&             playerData_;
  sf::RectangleShape      buttonShape_;
  sf::Text                buttonText_;
  std::function< void() > newCallback_;
};
} // namespace MenAmongGods

#endif