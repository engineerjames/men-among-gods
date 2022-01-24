#ifndef SKILL_DISPLAY_H
#define SKILL_DISPLAY_H

#include <SFML/Graphics.hpp>

class SkillDisplay : public sf::Drawable
{
public:
  struct SkillRow
  {
    sf::Text                            name_;
    sf::Text                            displayValue_;
    sf::Text                            expRequired_;
    static const constexpr unsigned int FONT_SIZE = 12;

    SkillRow();
    ~SkillRow() = default;
  };

  static const constexpr unsigned int MAX_SKILLS = 50;

  // TODO: Update font& to const font&
  SkillDisplay( sf::Font& font );
  ~SkillDisplay() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
  sf::Font&                          font_;
  std::array< SkillRow, MAX_SKILLS > skillNames_;
  const sf::Vector2f                 initialPosition_;
};

#endif
