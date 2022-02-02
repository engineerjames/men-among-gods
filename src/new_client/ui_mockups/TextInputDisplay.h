#ifndef TEXT_INPUT_DISPLAY_H
#define TEXT_INPUT_DISPLAY_H

#include <SFML/Graphics.hpp>

#include "Component.h"

namespace MenAmongGods
{
class TextInputDisplay : public MenAmongGods::Component
{
public:
  TextInputDisplay( const sf::RenderWindow& window, const sf::Font& font, unsigned int fontSize );
  virtual ~TextInputDisplay() = default;

  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

  void setPosition( sf::Vector2f newPosition );

  void deselect();

protected:
  const sf::RenderWindow& window_;
  sf::Text                text_;
  bool                    isSelected_;
  sf::RectangleShape      boundingBox_;
  std::string             backingText_;
  unsigned int            maxCharacters_;
};
} // namespace MenAmongGods

#endif