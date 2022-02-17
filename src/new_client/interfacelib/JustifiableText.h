#ifndef MEN_AMONG_GODS_JUSTIFIABLE_TEXT
#define MEN_AMONG_GODS_JUSTIFIABLE_TEXT

#include <SFML/Graphics.hpp>

#include "Component.h"

namespace MenAmongGods
{
class JustifiableText : public MenAmongGods::Component
{
public:
  enum struct TextJustification
  {
    LEFT,
    RIGHT,
    CENTER
  };

  // JustifiableText assumes that the position that the text occupies is the point at which (on the x-axis)
  // it is to justify to. That is, text position is the justification point.
  JustifiableText( const sf::Font& font, unsigned int characterSize,
                   std::string initialText = "" ); // TODO: Match constructor parameter ordering as sf::Text
  JustifiableText();

  ~JustifiableText() = default;

  void         setJustification( TextJustification mode );
  void         setString( const std::string& text );
  void         setPosition( sf::Vector2f newPosition );
  void         setFont( const sf::Font& font );
  void         setCharacterSize( unsigned int size );
  void         setFillColor( const sf::Color& color );
  void         setOutlineColor( const sf::Color& color );
  void         setCenterWidth( int newValue );
  virtual void update() override;

  virtual void onUserInput( const sf::Event& e ) override;

  // Finalize is called once at the end of every frame
  virtual void finalize() override;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  void moveTextAccordingToJustification();

  sf::Text          text_;
  bool              positionNeedsUpdating_;
  TextJustification justificationMode_;
  sf::Vector2f      cachedPosition_;

  // Only needed for "CENTER" justification
  int centerWidth_;
};
} // namespace MenAmongGods

#endif