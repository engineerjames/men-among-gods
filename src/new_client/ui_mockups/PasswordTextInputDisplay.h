#ifndef PASSWORD_TEXT_INPUT_DISPLAY_H
#define PASSWORD_TEXT_INPUT_DISPLAY_H

#include <SFML/Graphics.hpp>

#include "TextInputDisplay.h"

namespace MenAmongGods
{
class PasswordTextInputDisplay : public MenAmongGods::TextInputDisplay
{
public:
  PasswordTextInputDisplay( const sf::RenderWindow& window, const sf::Font& font, unsigned int fontSize );
  virtual ~PasswordTextInputDisplay() = default;

  virtual void onUserInput( const sf::Event& e ) override;
};
} // namespace MenAmongGods

#endif