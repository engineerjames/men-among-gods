#ifndef SKILL_DISPLAY_H
#define SKILL_DISPLAY_H

#include <array>
#include <SFML/Graphics.hpp>

#include "../ConstantIdentifiers.h"
#include "ColorPalette.h"
#include "Component.h"

class PlayerData;

class SkillsAndAttributes : public MenAmongGods::Component
{
public:
  struct SkillRow
  {
    sf::Text name_;
    sf::Text displayValue_;
    sf::Text expRequired_;
    sf::Text plus_;
    sf::Text minus_;

    SkillRow();
    ~SkillRow() = default;
  };

  SkillsAndAttributes( const sf::Font& font, PlayerData& playerData );
  ~SkillsAndAttributes() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

private:
  const sf::Font&                        font_;
  PlayerData&                            playerData_;
  std::array< SkillRow, MAX_ATTRIBUTES > attributes_;
  std::array< SkillRow, MAX_SKILLS >     skills_;
  std::array< SkillRow*, MAX_SKILLS >    skillsToDisplay_;
  sf::RectangleShape                     skillScrollBar_;
};

#endif
