#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SFML/Graphics.hpp>
#include <vector>

class TextBox : public sf::Drawable, public sf::Transformable
{
public:
  TextBox( const sf::Font& font );
  ~TextBox() = default;

  void         addMessage( const sf::Text& newMsg );
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  unsigned int getFontSize() const;

private:
  unsigned int    maxCharactersPerLine_;
  const sf::Font& font_;
  unsigned int    fontSize_;

  std::vector< sf::Text > messageLog_;
};

#endif