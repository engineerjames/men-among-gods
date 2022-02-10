#ifndef UI_POSITIONS_H
#define UI_POSITIONS_H

#include <SFML/Graphics.hpp>

namespace MenAmongGods
{

// Skill and attributes
static const sf::Vector2f initialAttributePosition { 3.0f, 1.0f };
static const sf::Vector2f initialSkillPosition { 3.0f, 113.0f };

// Gold display and rank "Private" displayed below the 'self' view
static const sf::Vector2f goldDisplayPosition { 452.0f, 185.0f };
static const sf::Vector2f textualRankPosition { 413.0f, 171.0f };

// User input text box
static const sf::Vector2f userInputPosition { 500.0f, 227.0f };

// Display beneath the message box with WV/AV/Exp
static const sf::Vector2f avLabelPosition { 645.0f, 255.0f };
static const sf::Vector2f avValuePosition { 792.0f, 255.0f };

static const sf::Vector2f wvLabelPosition { 645.0f, 241.0f };
static const sf::Vector2f wvValuePosition { 792.0f, 241.0f };

static const sf::Vector2f expLabelPosition { 645.0f, 269.0f };
static const sf::Vector2f expValuePosition { 792.0f, 269.0f };

// Hitpoints / End / Mana area near the bottom left
static const sf::Vector2f hpLabelPosition { 4.0f, 268.0f };
static const sf::Vector2f hpCurrentValuePosition { 111.0f, 268.0f };
static const sf::Vector2f hpMaxValuePosition { 136.0f, 268.0f };

static const sf::Vector2f endLabelPosition { 4.0f, 281.0f };
static const sf::Vector2f endCurrentValuePosition { 111.0f, 281.0f };
static const sf::Vector2f endMaxValuePosition { 136.0f, 281.0f };

static const sf::Vector2f manaLabelPosition { 4.0f, 295.0f };
static const sf::Vector2f manaCurrentValuePosition { 111.0f, 295.0f };
static const sf::Vector2f manaMaxValuePosition { 136.0f, 295.0f };

// Client options on the bottom-right
static const sf::Vector2f  clientOptionsOrigin { 608.0f, 555.0f };
static const constexpr int CLIENT_SELECTION_SPACING_X = 48;
static const constexpr int CLIENT_SELECTION_SPACING_Y = 15;
static const sf::Vector2f  CLIENT_SELECTION_BOX_SIZE { 45, 12 };

} // namespace MenAmongGods

#endif