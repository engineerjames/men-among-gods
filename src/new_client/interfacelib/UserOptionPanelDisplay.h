#ifndef MEN_AMONG_GODS_USER_OPTION_PANEL_DISPLAY
#define MEN_AMONG_GODS_USER_OPTION_PANEL_DISPLAY

#include "Component.h"

#include <SFML/Graphics.hpp>

#include <vector>

class PlayerData;

namespace MenAmongGods
{
class UserOptionPanelDisplay : MenAmongGods::Component
{
public:
  UserOptionPanelDisplay( PlayerData& playerData );

  // Component Interface
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  // sf::Drawable Interface
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  PlayerData& playerData_;

  sf::RectangleShape modeRectangle_;
  sf::RectangleShape hideWallsRectangle_;
  sf::RectangleShape hideNamesRectangle_;
  sf::RectangleShape hideHealthRectangle_;

  std::vector< sf::RectangleShape* > rectangles_;
};
} // namespace MenAmongGods

#endif