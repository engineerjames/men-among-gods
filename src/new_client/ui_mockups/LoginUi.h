#ifndef MEN_AMONG_GODS_LOGIN_UI_H
#define MEN_AMONG_GODS_LOGIN_UI_H

#include "Component.h"
#include "RadioButtonDisplay.h"
#include "TextInputDisplay.h"

#include <SFML/Graphics.hpp>

// Consider creating a radio button group class
#include <vector>

namespace MenAmongGods
{
class LoginUi : public MenAmongGods::Component
{
public:
  LoginUi( const sf::RenderWindow& window, const sf::Font& font );
  ~LoginUi() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;

  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

private:
  sf::Text                          nameLabel_;
  TextInputDisplay                  nameEntry_;
  sf::Text                          descriptionLabel_;
  TextInputDisplay                  descriptionEntry_;
  std::vector< RadioButtonDisplay > raceSelection_;
  std::vector< RadioButtonDisplay > sexSelection_;
};
} // namespace MenAmongGods

#endif