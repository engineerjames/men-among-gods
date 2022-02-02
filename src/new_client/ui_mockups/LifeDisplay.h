#ifndef LIFE_DISPLAY_H
#define LIFE_DISPLAY_H

#include "Component.h"
#include "SkillsAndAttributesDisplay.h"

namespace sf
{
class Font;
}

class PlayerData;

namespace MenAmongGods
{
class LifeDisplay : public MenAmongGods::Component
{
public:
  LifeDisplay( const sf::Font& font, PlayerData& playerData );
  virtual ~LifeDisplay() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

private:
  const sf::Font&                                font_;
  PlayerData&                                    playerData_;
  std::array< SkillsAndAttributesDisplay::SkillRow, 3 > lifeDisplay_;
};
} // namespace MenAmongGods

#endif