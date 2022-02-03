#ifndef MAIN_UI_H
#define MAIN_UI_H

#include <SFML/Graphics.hpp>

#include "Component.h"
#include "JustifiableText.h"
#include "LifeDisplay.h"
#include "PlayerInventoryDisplay.h"
#include "PlayerLogDisplay.h"
#include "PlayerTextInputDisplay.h"
#include "SkillsAndAttributesDisplay.h"

class PlayerData;

namespace MenAmongGods
{
class MainUi : public MenAmongGods::Component
{
public:
  enum struct LogType
  {
    INFO, // Yellow
    CHAT, // Blue
    LOG,  // Green
    ERROR // Red
  };

  MainUi( PlayerData& pdata, const GraphicsCache& gfxCache );
  ~MainUi() = default;

  void         addMessage( LogType type, std::string text );
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

private:
  PlayerData& playerData_;
  sf::Font    font_;

  sf::Text goldDisplay_;
  sf::Text textualRank_;

  sf::Text                      avLabel_;
  MenAmongGods::JustifiableText avValue_;

  sf::Text                      wvLabel_;
  MenAmongGods::JustifiableText wvValue_;

  sf::Text                      expLabel_;
  MenAmongGods::JustifiableText expValue_;

  sf::Text hpLabel_;
  sf::Text hpCurrentValue_;
  sf::Text hpMaxValue_;
  sf::Text endLabel_;
  sf::Text endCurrentValue_;
  sf::Text endMaxValue_;
  sf::Text manaLabel_;
  sf::Text manaCurrentValue_;
  sf::Text manaMaxValue_;

  SkillsAndAttributesDisplay skillsAndAttributes_;
  LifeDisplay         lifeDisplay_;

  PlayerLogDisplay       msgBox_;
  PlayerTextInputDisplay userInput_;
  PlayerInventoryDisplay playerInventory_;
};
} // namespace MenAmongGods
#endif