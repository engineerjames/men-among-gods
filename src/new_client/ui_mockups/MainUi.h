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
  sf::Font font_;

  sf::Text goldDisplay_;
  sf::Text textualRank_;

  sf::Text avLabel_;
  sf::Text avValue_;

  sf::Text wvLabel_;
  sf::Text wvValue_;

  sf::Text expLabel_;
  sf::Text expValue_;

  sf::Text hpLabel_;
  sf::Text hpCurrentValue_;
  sf::Text hpMaxValue_;
  sf::Text endLabel_;
  sf::Text endCurrentValue_;
  sf::Text endMaxValue_;
  sf::Text manaLabel_;
  sf::Text manaCurrentValue_;
  sf::Text manaMaxValue_;

  TextBox   msgBox_;
  TextInput userInput_;
};

#endif