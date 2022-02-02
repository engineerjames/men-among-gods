#ifndef SKILL_DISPLAY_H
#define SKILL_DISPLAY_H

#include <SFML/Graphics.hpp>
#include <array>

#include "../ConstantIdentifiers.h"
#include "ColorPalette.h"
#include "Component.h"
#include "JustifiableText.h"

class PlayerData;

class SkillsAndAttributesDisplay : public MenAmongGods::Component
{
public:
  struct SkillRow
  {
    sf::Text                      name_;
    MenAmongGods::JustifiableText displayValue_;
    MenAmongGods::JustifiableText expRequired_;
    sf::Text                      plus_;
    sf::Text                      minus_;

    SkillRow();
    ~SkillRow() = default;
  };

  SkillsAndAttributesDisplay( const sf::Font& font, PlayerData& playerData );
  ~SkillsAndAttributesDisplay() = default;

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
