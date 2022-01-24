#ifndef SKILL_DISPLAY_H
#define SKILL_DISPLAY_H

#include <SFML/Graphics.hpp>

#include "ColorPalette.h"

class SkillsAndAttributes : public sf::Drawable
{
public:
  struct SkillRow
  {
    sf::Text name_;
    sf::Text displayValue_;
    sf::Text expRequired_;
    sf::Text plus_;
    sf::Text minus_;

    static const constexpr unsigned int FONT_SIZE = 12;

    SkillRow();
    ~SkillRow() = default;
  };

  static const constexpr unsigned int MAX_SKILLS = 50;

  SkillsAndAttributes( const sf::Font& font );
  ~SkillsAndAttributes() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  const sf::Font&                    font_;
  std::array< SkillRow, 8 >          attributes_;
  std::array< SkillRow, MAX_SKILLS > skills_;
  const sf::Vector2f                 initialAttributePosition_;
  const sf::Vector2f                 initialSkillPosition_;
  sf::RectangleShape                 skillScrollBar_;
};
// Rectangle scroll bar: 207,149
#endif
