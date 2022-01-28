#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Component.h"

class TextInput : public sf::Text, public MenAmongGods::Component
{
public:
  TextInput( const sf::Font& font );
  virtual ~TextInput() override = default;

  void setPosition( const sf::Vector2f& newPosition );
  void getAndClearCommands( std::vector< std::string >& outList );

  virtual void update( ) override;
  virtual void onUserInput(const sf::Event& e) override;
  virtual void finalize() override;

private:
  unsigned int               maxCharacters_;
  const sf::Font&            font_;
  std::string                text_;
  std::vector< std::string > commandList_;
};

#endif