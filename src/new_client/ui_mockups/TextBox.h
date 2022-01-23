#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SFML/Graphics.hpp>
#include <vector>

class TextBox : public sf::Drawable, public sf::Transformable
{
public:
  enum struct LogType
  {
    INFO, // Yellow
    CHAT, // Blue
    LOG,  // Green
    ERROR // Red
  };

  TextBox();
  ~TextBox() = default;

  void         addMessage( LogType type, std::string text );
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  unsigned int maxCharactersPerLine_;
  sf::Font     font_;
  unsigned int fontSize_;

  // Filthy hack for now--TODO: Remove mutable designation from messageLog by pre-processing
  // the location tha should be displayed to the user
  mutable std::vector< sf::Text > messageLog_;
};

#endif