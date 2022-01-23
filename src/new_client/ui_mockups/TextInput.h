#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include <SFML/Graphics.hpp>
#include <vector>

class TextInput : public sf::Text
{
public:
  TextInput();
  virtual ~TextInput() override = default;

  void handleInput( sf::Event e );
  void setPosition( const sf::Vector2f& newPosition );
  void getAndClearCommands( std::vector< std::string >& outList );

private:
  unsigned int               maxCharacters_;
  sf::Font                   font_;
  std::string                text_;
  std::vector< std::string > commandList_;
};

#endif