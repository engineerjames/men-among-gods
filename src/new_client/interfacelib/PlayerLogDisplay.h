#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Component.h"

namespace MenAmongGods
{
class PlayerLogDisplay : public sf::Transformable, public MenAmongGods::Component
{
public:
  PlayerLogDisplay( const sf::RenderWindow& window );
  ~PlayerLogDisplay() = default;

  void         addMessage( sf::Text newMsg );
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;
  void         writeLogToFile( const std::string& pathToFile ) const;

private:
  void        recalculateMessagePositions();
  std::string splitStringWithNewlines( std::string& input );

  const sf::RenderWindow& window_;
  std::vector< sf::Text > messageLog_;
  const int               charactersPerLine_;
  int                     chatLogOffset_;
};
} // namespace MenAmongGods
#endif