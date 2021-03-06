#ifndef UI_POSITIONS_H
#define UI_POSITIONS_H

#include <SFML/Graphics.hpp>

namespace MenAmongGods
{

static const constexpr int   FONT_SIZE      = 10;
static const constexpr float LETTER_SPACING = 1.0f;

// Shop (and grave search) position
static const sf::Vector2f  shopPosition { 220.0f, 260.0f };
static const sf::Vector2f  closeShopButtonPosition { 500.0f, 260.0f };
static const sf::Vector2f  closeShopButtonSize { 20.0f, 20.0f };
static const sf::FloatRect closeShopButtonBoundingBox { closeShopButtonPosition, closeShopButtonSize };

// Player sprite position (the one in the UI, not the map)
static const sf::Vector2f playerSpritePosition { 402.0f, 32.0f };

// Skill and attributes
static const sf::Vector2f initialAttributePosition { 3.0f, 1.0f };
static const sf::Vector2f initialSkillPosition { 3.0f, 113.0f };

static const sf::Vector2f scrollBarMovementPerClick { 0.0f, 3.0f };

static const sf::Vector2f  plusAreaRectanglePosition { 134.0f, 2.0f };
static const sf::Vector2f  plusAreaRectangleSize { 10.0f, 248.0f };
static const sf::FloatRect plusAreaRectangle { plusAreaRectanglePosition, plusAreaRectangleSize };

static const sf::Vector2f  minusAreaRectanglePosition { 147.0f, 2.0f };
static const sf::Vector2f  minusAreaRectangleSize { 10.0f, 248.0f };
static const sf::FloatRect minusAreaRectangle { minusAreaRectanglePosition, minusAreaRectangleSize };

static const sf::Vector2f scrollUpBoxPosition { 207.0f, 114.0f };
static const sf::Vector2f scrollDownBoxPosition { 207.0f, 219.0f };
static const sf::Vector2f scrollBoxSize { 10.0f, 32.0f };

// Gold display and rank "Private" displayed below the 'self' view
static const sf::Vector2f goldLabelPosition { 375.0f, 186.0f };
static const sf::Vector2f goldDisplayPosition { 495.0f, 186.0 };
static const sf::Vector2f textualRankPosition { 377.0f, 169.0f };
static const sf::Vector2f playerNamePosition { 417.0f, 27.0f };

// Inventory positions (size is the same as for the skills)
static const sf::Vector2f inventoryScrollUpBoxPosition { 291.0f, 3.0f };
static const sf::Vector2f inventoryScrollDownBoxPosition { 291.0f, 139.0f };
static const sf::Vector2f inventoryScrollBarPosition { 290.0f, 36.0f };
static const sf::Vector2f inventoryScrollBarSize { 11.0f, 15.0f };

static const sf::Vector2f  inventoryBoundingBoxPosition { 220.0f, 3.0f };
static const sf::Vector2f  inventoryBoundingBoxSize { 66.0f, 172.0f };
static const sf::FloatRect inventoryBoundingBox { inventoryBoundingBoxPosition, inventoryBoundingBoxSize };

static const sf::Vector2f  equipmentBoundingBoxPosition { 304.0f, 3.0f };
static const sf::Vector2f  equipmentBoundingBoxSize { 66.0f, 206.0f };
static const sf::FloatRect equipmentBoundingBox { equipmentBoundingBoxPosition, equipmentBoundingBoxSize };

static const sf::Vector2f  skillsBoundingBoxPosition { 0.0f, 114.0f };
static const sf::Vector2f  skillsBoundingBoxSize { 206.0f, 140.0f };
static const sf::FloatRect skillsBoundingBox { skillsBoundingBoxPosition, skillsBoundingBoxSize };

// User input text box
static const sf::Vector2f userInputPosition { 500.0f, 227.0f };

// Display beneath the message box with WV/AV/Exp
static const sf::Vector2f avLabelPosition { 645.0f, 255.0f };
static const sf::Vector2f avValuePosition { 792.0f, 255.0f };

static const sf::Vector2f wvLabelPosition { 645.0f, 241.0f };
static const sf::Vector2f wvValuePosition { 792.0f, 241.0f };

static const sf::Vector2f expLabelPosition { 645.0f, 269.0f };
static const sf::Vector2f expValuePosition { 792.0f, 269.0f };

static const sf::Vector2f expToSpendLabelPosition { 115.0f, 255.0f };
static const sf::Vector2f expToSpendValuePosition { 203.0f, 255.0f };

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

// Chat log location
static const sf::Vector2f  chatLogPosition { 500.0f, 3.0f };
static const sf::Vector2f  chatLogSize { 300.0f, 235.0f };
static const sf::FloatRect chatLogBoundingBox { chatLogPosition, chatLogSize };

// Client options on the bottom-right
static const sf::Vector2f  clientOptionsOrigin { 608.0f, 555.0f };
static const constexpr int CLIENT_SELECTION_SPACING_X = 48;
static const constexpr int CLIENT_SELECTION_SPACING_Y = 15;
static const sf::Vector2f  CLIENT_SELECTION_BOX_SIZE { 45, 12 };

static const sf::Vector2f xButtonOrigin { 608.0f, 505.0f };

} // namespace MenAmongGods

#endif