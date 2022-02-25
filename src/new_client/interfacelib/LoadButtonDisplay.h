#ifndef MEN_AMONG_GODS_LOAD_BUTTON_DISPLAY_H
#define MEN_AMONG_GODS_LOAD_BUTTON_DISPLAY_H

#include "Component.h"

#include <SFML/Graphics.hpp>
#include <filesystem>

class PlayerData;

namespace MenAmongGods
{
class LoadButtonDisplay : public MenAmongGods::Component
{
public:
  LoadButtonDisplay( const sf::RenderWindow& window, PlayerData& playerData, const sf::Font& font, const unsigned int fontSize,
                     sf::Vector2f buttonSize );
  virtual ~LoadButtonDisplay() = default;

  void setPosition( const sf::Vector2f& newPosition );

  // Component interface
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  // sf::Drawable interface
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  const sf::RenderWindow&              window_;
  PlayerData&                          playerData_;
  sf::RectangleShape                   buttonShape_;
  sf::Text                             buttonText_;
  std::vector< std::filesystem::path > paths_;
  std::vector< sf::Text >              fileList_;
};
} // namespace MenAmongGods

#endif