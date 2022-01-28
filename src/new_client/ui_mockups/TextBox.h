#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SFML/Graphics.hpp>
#include <vector>

class TextBox : public sf::Drawable, public sf::Transformable
{
public:
  TextBox();
  ~TextBox() = default;

  void         addMessage( const sf::Text& newMsg );
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  void         writeLogToFile( const std::string& pathToFile ) const;

private:
  std::vector< sf::Text > messageLog_;
};

#endif