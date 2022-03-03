#ifndef MEN_AMONG_GODS_SKILLS_AND_ATTRIBUTES_DISPLAY
#define MEN_AMONG_GODS_SKILLS_AND_ATTRIBUTES_DISPLAY

#include <SFML/Graphics.hpp>
#include <array>
#include <map>
#include <stack>
#include <string>
#include <vector>

#include "ColorPalette.h"
#include "Component.h"
#include "ConstantIdentifiers.h"
#include "JustifiableText.h"

class PlayerData;
class GraphicsCache;
class GraphicsIndex;

namespace MenAmongGods
{
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
    int                           skillsIndex_;

    SkillRow();
    ~SkillRow() = default;
  };

  SkillsAndAttributesDisplay( const sf::RenderWindow& window, const sf::Font& font, GraphicsCache& gfxCache, const GraphicsIndex& gfxIndex,
                              PlayerData& playerData );
  ~SkillsAndAttributesDisplay() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

private:
  const sf::RenderWindow&                    window_;
  const sf::Font&                            font_;
  GraphicsCache&                             gfxCache_;
  const GraphicsIndex&                       gfxIndex_;
  PlayerData&                                playerData_;
  std::array< SkillRow, MAX_ATTRIBUTES >     attributes_;
  std::array< SkillRow, 3 >                  lifeDisplay_;
  std::array< SkillRow, MAX_SKILLS >         skills_;
  std::array< SkillRow*, MAX_SKILLS >        skillsToDisplay_;
  sf::RectangleShape                         skillScrollBar_;
  sf::FloatRect                              scrollUpBox_;
  sf::FloatRect                              scrollDownBox_;
  int                                        scrollPosition_;
  const sf::Vector2f                         initialScrollBarPosition_;
  std::vector< sf::Sprite >                  spellsToDraw;
  sf::Text                                   expToSpendLabel_;
  MenAmongGods::JustifiableText              expToSpendValue_;
  std::map< std::string, std::stack< int > > raiseMap_; // TODO: This should be in the player data class
  int                                        totalPointsToSpend_;
};
} // namespace MenAmongGods

#endif
