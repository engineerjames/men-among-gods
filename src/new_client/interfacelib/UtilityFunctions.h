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

inline bool userClickedOnMap( const sf::Vector2f& pos )
{
  sf::FloatRect skillsArea { sf::Vector2f { 0.0f, 0.0f }, sf::Vector2f { 248.0f, 280.0f } };
  sf::FloatRect clientOptionsArea { sf::Vector2f { 600.0f, 500.0 }, sf::Vector2f { 200.0f, 100.0f } };

  // TODO: This needs some work, currently just a rough approximation
  if ( skillsArea.contains( pos ) || clientOptionsArea.contains( pos ) )
  {
    return false;
  }

  return true;
}

} // namespace MenAmongGods
#endif