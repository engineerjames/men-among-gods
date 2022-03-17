#include "MiniMapDisplay.h"

#include "ColorPalette.h"
#include "GraphicsCache.h"
#include "Map.h"
#include "MapConstants.h"

namespace MenAmongGods
{

MiniMapDisplay::MiniMapDisplay( MenAmongGods::Map& map, GraphicsCache& cache )
    : MenAmongGods::Component()
    , map_( map )
    , cache_( cache )
    , miniMap_()
    , miniMapPixelsToDraw_()
{
  for ( auto&& rect : miniMap_ )
  {
    rect.setFillColor( sf::Color { 0x000000FF } );
  }
}

void MiniMapDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( const auto& pixel : miniMapPixelsToDraw_ )
  {
    target.draw( pixel, states );
  }
}

void MiniMapDisplay::finalize()
{
}

void MiniMapDisplay::onUserInput( const sf::Event& )
{
}

void MiniMapDisplay::update()
{
  // TODO: Investigate why placing this backwards makes the minimap work.  Originally the x and y positions were swapped.
  int mapY_ = map_.getX( ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX );
  int mapX_ = map_.getY( ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX );

  for ( int y = TILEY - 1; y >= 0; y-- )
  {
    for ( int x = 0; x < TILEX; x++ )
    {
      int m = x + y * MAPX;

      if ( map_.getX( m ) < 1024 && map_.getY( m ) < 1024 && ! ( map_.getFlags( m ) & INVIS ) )
      {
        if ( miniMap_[ map_.getY( m ) + map_.getX( m ) * 1024 ].getFillColor().r != 255u &&
             miniMap_[ map_.getY( m ) + map_.getX( m ) * 1024 ].getFillColor().g != 255u &&
             miniMap_[ map_.getY( m ) + map_.getX( m ) * 1024 ].getFillColor().b != 255u )

          if ( cache_.getAvgColor( map_.getBackgroundSprite( m ) ) != MenAmongGods::AverageBlack )
          {
            miniMap_[ map_.getY( m ) + map_.getX( m ) * 1024 ].setFillColor( cache_.getAvgColor( map_.getBackgroundSprite( m ) ) );
          }
      }

      if ( map_.getObject1( m ) && map_.getX( m ) < 1024 && map_.getY( m ) < 1024 )
      {
        if ( cache_.getAvgColor( map_.getObject1( m ) ) != MenAmongGods::AverageBlack )
        {
          miniMap_[ map_.getY( m ) + map_.getX( m ) * 1024 ].setFillColor( cache_.getAvgColor( map_.getObject1( m ) ) );
        }
      }
    }
  }

  mapX_ -= 64;
  if ( mapX_ < 0 )
    mapX_ = 0;
  if ( mapX_ > 1023 - 128 )
    mapX_ = 1023 - 128;

  mapY_ = mapY_ - 64;
  if ( mapY_ < 0 )
    mapY_ = 0;
  if ( mapY_ > 1023 - 128 )
    mapY_ = 1023 - 128;

  for ( int y = 0; y < 128; ++y )
  {
    int s = ( y + mapY_ ) * 1024 + mapX_;

    for ( int x = 0; x < 128; ++x )
    {
      sf::RectangleShape newRect = miniMap_[ s++ ];
      float              xPos    = static_cast< float >( 3 + x );
      float              yPos    = static_cast< float >( 471 + y );
      newRect.setSize( sf::Vector2f { 1.0f, 1.0f } );
      newRect.setPosition( sf::Vector2f { xPos, yPos } );

      miniMapPixelsToDraw_[ y * 128 + x ] = newRect;
    }
  }
}
} // namespace MenAmongGods