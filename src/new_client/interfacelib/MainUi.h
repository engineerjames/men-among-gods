#ifndef MEN_AMONG_GODS_MAIN_UI_H
#define MEN_AMONG_GODS_MAIN_UI_H

#include <SFML/Graphics.hpp>

#include "ClientTypes.h"
#include "Component.h"
#include "JustifiableText.h"
#include "LifeDisplay.h"
#include "MapDisplay.h"
#include "PlayerInventoryDisplay.h"
#include "PlayerLogDisplay.h"
#include "PlayerTextInputDisplay.h"
#include "RankDisplay.h"
#include "SkillsAndAttributesDisplay.h"
#include "UserOptionPanelDisplay.h"

class PlayerData;
class GraphicsCache;
class GraphicsIndex;
class Map;

namespace MenAmongGods
{
class FontCache;

class MainUi : public MenAmongGods::Component
{
public:
  MainUi( const sf::RenderWindow& window, Map& map, PlayerData& pdata, const GraphicsCache& gfxCache, const GraphicsIndex& gfxIndex,
          const FontCache& fontCache );
  ~MainUi() = default;

  void         addMessage( LogType type, std::string text );
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  virtual void populateCommands( std::vector< std::shared_ptr< ClientCommand > >& outCommands ) override;

private:
  PlayerData& playerData_;
  sf::Font    font_;

  sf::Text goldDisplay_;

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
  LifeDisplay                lifeDisplay_;

  PlayerLogDisplay       msgBox_;
  PlayerTextInputDisplay userInput_;
  PlayerInventoryDisplay playerInventory_;
  UserOptionPanelDisplay userOptionPanel_;
  MapDisplay             mapDisplay_;
  RankDisplay            rankDisplay_;

  sf::Sprite background_;
};
} // namespace MenAmongGods
#endif