#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Component.h"

class TextBox : public sf::Drawable, public sf::Transformable, public MenAmongGods::Component
{
public:
  TextBox();
  ~TextBox() = default;

  void         addMessage( const sf::Text& newMsg );
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;
  void         writeLogToFile( const std::string& pathToFile ) const;

private:
  std::vector< sf::Text > messageLog_;
};

#endif