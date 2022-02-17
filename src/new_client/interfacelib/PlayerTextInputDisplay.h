#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Component.h"

namespace MenAmongGods
{
class PlayerTextInputDisplay : public MenAmongGods::Component
{
public:
  PlayerTextInputDisplay( const sf::Font& font );
  virtual ~PlayerTextInputDisplay() override = default;

  void setPosition( const sf::Vector2f& newPosition );

  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  sf::Text        drawableText_;
  unsigned int    maxCharacters_;
  const sf::Font& font_;
  std::string     text_;
};
} // namespace MenAmongGods
#endif