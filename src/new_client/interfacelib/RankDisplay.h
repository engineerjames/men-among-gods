#ifndef MEN_AMONG_GODS_RANK_DISPLAY_H
#define MEN_AMONG_GODS_RANK_DISPLAY_H

#include <SFML/Graphics.hpp>

#include "Component.h"
#include "JustifiableText.h"

class GraphicsCache;
class PlayerData;

namespace MenAmongGods
{
class RankDisplay : public MenAmongGods::Component
{
public:
  RankDisplay( const sf::Font& font, PlayerData& playerData, GraphicsCache& gfxCache );
  virtual ~RankDisplay() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;
  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

private:
  const sf::Font& font_;
  GraphicsCache&  gfxCache_;
  PlayerData&     playerData_;
  JustifiableText textualRank_;
  sf::Sprite      rankSprite_;
};
} // namespace MenAmongGods

#endif