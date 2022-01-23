#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SFML/Graphics.hpp>
#include <vector>

class TextBox
{
public:
  TextBox();
  ~TextBox() = default;

private:
  unsigned int               maxCharacters_;
  sf::Font                   font_;
  std::string                text_;
  std::vector< std::string > commandList_;
};

#endif