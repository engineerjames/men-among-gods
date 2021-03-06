#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <array>
#include <set>

#include "MapConstants.h"
#include "UiConstants.h"

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
  if ( skillsArea.contains( pos ) || clientOptionsArea.contains( pos ) || inventoryBoundingBox.contains( pos ) ||
       equipmentBoundingBox.contains( pos ) )
  {
    return false;
  }

  return true;
}

inline int getMapIndexFromMousePosition( const sf::Vector2f& mousePosition )
{
  sf::Vector2f shiftedMousePosition = sf::Vector2f { mousePosition.x + ( 176 - 16 ), mousePosition.y + 8 };

  int mx = static_cast< int >( 2 * shiftedMousePosition.y + shiftedMousePosition.x - ( YPOS * 2 ) - XPOS + ( ( TILEX - 34 ) / 2 * 32 ) );
  int my = static_cast< int >( shiftedMousePosition.x - 2 * shiftedMousePosition.y + ( YPOS * 2 ) - XPOS + ( ( TILEX - 34 ) / 2 * 32 ) );

  mx /= 32;
  my /= 32;

  // Map index
  return mx + my * TILEX;
}

inline std::set<int> getFuzzyMapIndices( sf::Vector2f centerMousePosition )
{
  int m = getMapIndexFromMousePosition( centerMousePosition );

  std::set< int > mapIndicesToCheck {};
  
  // First check exactly where the mouse cursor is (just in-case)
  mapIndicesToCheck.insert( m );

  const int N_POINTS_X = 10;
  const int N_POINTS_Y = 10;

  for (int i = 0; i < N_POINTS_X; ++i)
  {
    for (int j = 0; j < N_POINTS_Y; ++j)
    {
      float xOffset = -16.0f + ( i * (  32.0f / ( N_POINTS_X - 1 ) ) );
      float yOffset = 64.0f - ( j * ( 48.0f / ( N_POINTS_Y - 1 ) ) );

      int newIndexToCheck = getMapIndexFromMousePosition( centerMousePosition + sf::Vector2f { xOffset, yOffset } );    

      mapIndicesToCheck.insert( newIndexToCheck );
    }
  }

  return mapIndicesToCheck;
}

} // namespace MenAmongGods
#endif