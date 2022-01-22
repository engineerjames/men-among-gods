#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include <SFML/Graphics.hpp>

class TextInput : public sf::Drawable, public sf::Transformable
{
public:
  TextInput();
  ~TextInput() = default;

  void handleInput( sf::Event e );

private:
  unsigned int       sizeInPixels_;
  sf::Font           font_;
  std::string        text_;
  sf::RectangleShape boundingBox_;
};

#endif