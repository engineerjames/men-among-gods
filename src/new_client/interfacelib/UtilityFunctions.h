#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include <SFML/Graphics.hpp>

#include "ConstantIdentifiers.h"

namespace MenAmongGods
{
inline sf::Vector2f getNormalizedMousePosition( const sf::RenderWindow& window )
{
  sf::Vector2f mousePosition = sf::Vector2f { static_cast< float >( sf::Mouse::getPosition( window ).x ),
                                              static_cast< float >( sf::Mouse::getPosition( window ).y ) };

  sf::Vector2f windowSize       = window.getView().getSize();
  sf::Vector2f windowResolution = sf::Vector2f { static_cast< float >( window.getSize().x ), static_cast< float >( window.getSize().y ) };
  sf::Vector2f multiplicationFactor = sf::Vector2f { windowSize.x / windowResolution.x, windowSize.y / windowResolution.y };

  sf::Vector2f normalizedMousePosition =
      sf::Vector2f { mousePosition.x * multiplicationFactor.x, mousePosition.y * multiplicationFactor.y };

  return normalizedMousePosition;
}

inline bool mapIndexIsValid( const int index )
{
  return index < ( TILEX * TILEY );
}

} // namespace MenAmongGods
#endif