#ifndef MEN_AMONG_GODS_USER_OPTION_PANEL_DISPLAY
#define MEN_AMONG_GODS_USER_OPTION_PANEL_DISPLAY

#include "Component.h"

#include <SFML/Graphics.hpp>

#include <vector>

class PlayerData;

namespace MenAmongGods
{
class UserOptionPanelDisplay : public MenAmongGods::Component
{
public:
  UserOptionPanelDisplay( const sf::RenderWindow& window, PlayerData& playerData );

  // Component Interface
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  // sf::Drawable Interface
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  const sf::RenderWindow& window_;
  PlayerData&             playerData_;

  sf::RectangleShape fastModeRectangle_;
  sf::RectangleShape normModeRectangle_;
  sf::RectangleShape slowModeRectangle_;

  sf::RectangleShape hideWallsRectangle_;
  sf::RectangleShape hideNamesRectangle_;
  sf::RectangleShape hideHealthRectangle_;

  std::vector< sf::RectangleShape* > rectangles_;
};
} // namespace MenAmongGods

#endif