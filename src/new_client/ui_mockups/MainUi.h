#ifndef MAIN_UI_H
#define MAIN_UI_H

#include <SFML/Graphics.hpp>

#include "TextBox.h"
#include "TextInput.h"

class MainUi : public sf::Drawable
{
public:
  enum struct LogType
  {
    INFO, // Yellow
    CHAT, // Blue
    LOG,  // Green
    ERROR // Red
  };

  MainUi();
  ~MainUi() = default;

  void         addMessage( LogType type, std::string text );
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  void         handleInput( sf::Event e );

private:
  sf::Text  goldDisplay_;
  sf::Text  textualRank_;
  sf::Font  font_;
  TextBox   msgBox_;
  TextInput userInput_;
};

#endif