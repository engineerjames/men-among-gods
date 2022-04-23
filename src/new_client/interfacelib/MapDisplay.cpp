#include "MapDisplay.h"

#include <fstream>
#include <iostream>
#include <set>

#include "ClientConfiguration.h"
#include "ColorPalette.h"
#include "DriverConstants.h"
#include "GraphicsCache.h"
#include "GraphicsIndex.h"
#include "Map.h"
#include "PlayerData.h"
#include "TickBuffer.h"
#include "UtilityFunctions.h"

// Commands
#include "AttackCommand.h"
#include "DropCommand.h"
#include "GiveCommand.h"
#include "LookCommand.h"
#include "LookItemCommand.h"
#include "MoveCommand.h"
#include "PickupCommand.h"
#include "TurnCommand.h"
#include "UseCommand.h"

namespace
{

int autohide( int x, int y )
{
  if ( x >= ( TILEX / 2 ) || ( y <= TILEX / 2 ) )
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int facing( int x, int y, int dir )
{
  if ( dir == 1 && x == TILEX / 2 + 1 && y == TILEY / 2 )
  {
    return 1;
  }
  if ( dir == 2 && x == TILEX / 2 - 1 && y == TILEY / 2 )
  {
    return 1;
  }
  if ( dir == 4 && x == TILEX / 2 && y == TILEY / 2 + 1 )
  {
    return 1;
  }
  if ( dir == 3 && x == TILEX / 2 && y == TILEY / 2 - 1 )
  {
    return 1;
  }

  return 0;
}

} // namespace

namespace MenAmongGods
{

MapDisplay::MapSpriteIterator MapDisplay::getSpriteByType( const std::set< int >& mapIndicesToCheck, MapSprite::SpriteType spriteType )
{
  auto sprite = std::find_if( std::begin( spritesToDraw_ ), std::end( spritesToDraw_ ),
                              [ & ]( const MapSprite& mapSprite )
                              {
                                for ( const auto& mapI : mapIndicesToCheck )
                                {
                                  if ( mapSprite.type == spriteType && mapSprite.index == mapI )
                                  {
                                    return true;
                                  }
                                }

                                return false;
                              } );

  return sprite;
}

MapDisplay::MapDisplay( const sf::Font& font, MenAmongGods::Map& map, PlayerData& playerData, GraphicsCache& cache,
                        const GraphicsIndex& index, const sf::RenderWindow& window )
    : MenAmongGods::Component()
    , font_( font )
    , map_( map )
    , playerData_( playerData )
    , cache_( cache )
    , index_( index )
    , window_( window )
    , spritesToDraw_()
    , textToDraw_()
    , healthBarsToDraw_()
    , tileType_()
    , tileX_()
    , tileY_()
{
}

void MapDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  for ( int i = 0; i < static_cast< int >( spritesToDraw_.size() ); ++i )
  {
    target.draw( spritesToDraw_[ i ].sprite, spritesToDraw_[ i ].renderState );
  }

  states.blendMode = sf::BlendAlpha;

  for ( const auto& text : textToDraw_ )
  {
    target.draw( text, states );
  }

  for ( const auto& hb : healthBarsToDraw_ )
  {
    target.draw( hb, states );
  }
}

void MapDisplay::finalize()
{
}

void MapDisplay::onUserInput( const sf::Event& e )
{
  // User attempts to move by left clicking on the map ( NOT holding down alt, shift, or control )
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left &&
       ! sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LShift ) && ! sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LAlt ) &&
       ! sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LControl ) )
  {
    if ( playerData_.getShouldShowShop() )
    {
      return;
    }

    // Attempting to port similar logic from inter.c::mouse_mapbox()
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    int m = getMapIndexFromMousePosition( mousePosition );

    if ( mapIndexIsValid( m ) && userClickedOnMap( mousePosition ) )
    {
      commands_.emplace_back( std::make_shared< MenAmongGods::MoveCommand >( map_.getX( m ), map_.getY( m ) ) );
    }

    return;
  }

  // User attempts to select a character
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left &&
       sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LAlt ) )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    for ( const auto& i : getFuzzyMapIndices( mousePosition ) )
    {
      int characterId = map_.getCharacterId( i );
      if ( characterId != 0 )
      {
        if ( playerData_.getSelectedCharacter() == characterId )
        {
          playerData_.setSelectedCharacter( 0 );
          return;
        }
        else
        {
          playerData_.setSelectedCharacter( characterId );
          return;
        }
      }
    }

    // If nothing was found, de-select as well.
    playerData_.setSelectedCharacter( 0 );
    return;
  }

  // User attempts to look at a character
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Right &&
       sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LControl ) )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    for ( const auto& i : getFuzzyMapIndices( mousePosition ) )
    {
      int characterId = map_.getCharacterId( i );
      if ( characterId != 0 )
      {
        commands_.push_back( std::make_shared< MenAmongGods::LookCommand >( characterId ) );
        return;
      }
    }
  }

  // User faces his/her character a specific direction via a right mouse button click
  if ( e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Right &&
       ! sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LShift ) )
  {
    // Attempting to port similar logic from inter.c::mouse_mapbox()
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    int m = getMapIndexFromMousePosition( mousePosition );

    if ( mapIndexIsValid( m ) )
    {
      commands_.emplace_back( std::make_shared< MenAmongGods::TurnCommand >( map_.getX( m ), map_.getY( m ) ) );
    }

    return;
  }

  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LControl ) && e.type == sf::Event::MouseButtonReleased &&
       e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    for ( const auto& i : getFuzzyMapIndices( mousePosition ) )
    {
      int characterId = map_.getCharacterId( i );
      // Check if character is present on tile?
      if ( characterId != 0 )
      {
        if ( playerData_.getCarriedItem() == 0 )
        {
          commands_.emplace_back( std::make_shared< MenAmongGods::AttackCommand >( characterId ) );
          return;
        }
        else
        {
          commands_.emplace_back( std::make_shared< MenAmongGods::GiveCommand >( characterId ) );
          return;
        }
      }
    }
  }

  // PICKUP or drop items
  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LShift ) && e.type == sf::Event::MouseButtonReleased &&
       e.mouseButton.button == sf::Mouse::Button::Left )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    for ( const auto& i : getFuzzyMapIndices( mousePosition ) )
    {
      cmap clickedTile = map_.getMap( i );

      if ( playerData_.getHoverState() != PlayerData::HoverState::NONE && lastHoveredIndex_ != 0 )
      {
        clickedTile = map_.getMap( lastHoveredIndex_ );
      }

      const int x = clickedTile.x;
      const int y = clickedTile.y;

      if ( x == 0 && y == 0 )
      {
        return;
      }

      if ( playerData_.getCarriedItem() != 0 && ! ( clickedTile.flags & ISITEM ) )
      {
        commands_.emplace_back( std::make_shared< MenAmongGods::DropCommand >( x, y ) );
        return;
      }

      if ( clickedTile.flags & ISITEM )
      {
        if ( clickedTile.flags & ISUSABLE )
        {
          commands_.emplace_back( std::make_shared< MenAmongGods::UseCommand >( x, y ) );
        }
        else
        {
          commands_.emplace_back( std::make_shared< MenAmongGods::PickupCommand >( x, y ) );
        }

        return;
      }
    }
  }

  // Look at item on the ground
  if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::LShift ) && e.type == sf::Event::MouseButtonReleased &&
       e.mouseButton.button == sf::Mouse::Button::Right )
  {
    sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

    if ( ! userClickedOnMap( mousePosition ) )
    {
      return;
    }

    int m = getMapIndexFromMousePosition( mousePosition );

    cmap      clickedTile = map_.getMap( m );
    const int x           = clickedTile.x;
    const int y           = clickedTile.y;
    if ( map_.getFlags( m ) & ISITEM )
    {
      commands_.emplace_back( std::make_shared< MenAmongGods::LookItemCommand >( x, y ) );
    }

    return;
  }
}

sf::Vector2i MapDisplay::dd_gputtext( int xpos, int ypos, std::string text, int xoff, int yoff )
{
  int rx = static_cast< int >( ( xpos / 2 ) + ( ypos / 2 ) + 32 - ( ( text.length() * 5 ) / 2 ) + XPOS );
  if ( xpos < 0 && ( xpos & 1 ) )
  {
    rx--;
  }
  if ( ypos < 0 && ( ypos & 1 ) )
  {
    rx--;
  }
  int ry = static_cast< int >( ( xpos / 4 ) - ( ypos / 4 ) + YPOS - 64 );
  if ( xpos < 0 && ( xpos & 3 ) )
  {
    ry--;
  }
  if ( ypos < 0 && ( ypos & 3 ) )
  {
    ry++;
  }

  rx += xoff;
  ry += yoff;

  return sf::Vector2i { rx, ry };
}

void MapDisplay::update()
{
  spritesToDraw_.clear();
  textToDraw_.clear();
  healthBarsToDraw_.clear();

  int x {};
  int y {};
  int tmp {};
  int selected_visible {};
  int alpha {};
  int alphastr {};
  int selected_char = playerData_.getSelectedCharacter();

  int xoff       = -map_.getObjectXOffset( ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX ) - 176; //-176;
  int yoff       = -map_.getObjectYOffset( ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX );       //-176;
  int plr_sprite = map_.getObject2( ( TILEX / 2 ) + ( TILEY / 2 ) * MAPX );

  playerData_.setPlayerSprite( plr_sprite );

  for ( y = TILEY - 1; y >= 0; y-- )
  {
    for ( x = 0; x < TILEX; x++ )
    {
      // background
      int m = x + y * MAPX;

      tmp = 0;

      if ( map_.getFlags( m ) & INVIS )
      {
        tmp |= 64;
      }
      if ( map_.getFlags( m ) & INFRARED )
      {
        tmp |= 256;
      }
      if ( map_.getFlags( m ) & UWATER )
      {
        tmp |= 512;
      }

      // Most of the floor tiles are 32x32 images
      // The tile itself is on the lower portion of the image
      // 32 px wide and 22px tall approximately
      // xs / ys are the x and y size in tiles (width / 32), and height / 32 respectively

      // What is the difference between ba_sprite and back? Can I always use ba_sprite?
      // by using ba_sprite instead; we fixed the intermittent "blank" sprite issue
      copysprite( m, map_.getBackgroundSprite( m ), map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff, map_.getLight( m ),
                  MapSprite::SpriteType::Tile );

      if ( playerData_.getGotoPosition().x == map_.getX( m ) && playerData_.getGotoPosition().y == map_.getY( m ) )
      {
        copysprite( m, 31, 0, x * 32, y * 32, xoff, yoff, 0, MapSprite::SpriteType::Tile );
      }
    }
  }

  // Exit early if the player has left to avoid drawing text and other such things
  // on the screen unnecessarily
  if ( playerData_.getExitFlag())
  {
    return;
  }

  for ( y = TILEY - 1; y >= 0; y-- )
  {
    for ( x = 0; x < TILEX; x++ )
    {
      int m = x + y * MAPX;

      if ( map_.getFlags( m ) & INVIS )
      {
        tmp = 128;
      }
      else
      {
        tmp = 0;
      }

      // object
      if ( playerData_.areWallsHidden() == 0 || ( map_.getFlags( m ) & ISITEM ) || autohide( x, y ) )
      {
        int tmp2 {};

        if ( map_.getObject1( m ) > 16335 && map_.getObject1( m ) < 16422 && map_.getObject1( m ) != 16357 &&
             map_.getObject1( m ) != 16365 && map_.getObject1( m ) != 16373 && map_.getObject1( m ) != 16381 &&
             map_.getObject1( m ) != 16357 && map_.getObject1( m ) != 16389 && map_.getObject1( m ) != 16397 &&
             map_.getObject1( m ) != 16405 && map_.getObject1( m ) != 16413 && map_.getObject1( m ) != 16421 &&
             ! facing( x, y, playerData_.getPlayerDirection() ) && ! autohide( x, y ) && playerData_.areWallsHidden() )
        { // mine hack
          if ( map_.getObject1( m ) < 16358 )
          {
            tmp2 = 457;
          }
          else if ( map_.getObject1( m ) < 16366 )
          {
            tmp2 = 456;
          }
          else if ( map_.getObject1( m ) < 16374 )
          {
            tmp2 = 455;
          }
          else if ( map_.getObject1( m ) < 16382 )
          {
            tmp2 = 466;
          }
          else if ( map_.getObject1( m ) < 16390 )
          {
            tmp2 = 459;
          }
          else if ( map_.getObject1( m ) < 16398 )
          {
            tmp2 = 458;
          }
          else if ( map_.getObject1( m ) < 16398 )
          {
            tmp2 = 449;
          }
          else if ( map_.getObject1( m ) < 16406 )
          {
            tmp2 = 468;
          }
          else
          {
            tmp2 = 467;
          }
        }
        else
        {
          copysprite( m, map_.getObject1( m ), map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff, map_.getLight( m ),
                      MapSprite::SpriteType::Object );
        }
      }
      else if ( map_.getObject1( m ) )
      {
        copysprite( m, map_.getObject1( m ) + 1, map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff, map_.getLight( m ),
                    MapSprite::SpriteType::Object );
      }

      // character
      if ( tileType_ == 2 && tileX_ == x && tileY_ == y )
      {
        tmp = 16;
      }
      else
      {
        tmp = 0;
      }

      if ( map_.getCharacterId( m ) == selected_char )
      {
        tmp |= 32;
        selected_visible = 1;
      }

      if ( map_.getFlags( m ) & INVIS )
      {
        tmp |= 64;
      }
      if ( map_.getFlags( m ) & STONED )
      {
        tmp |= 128;
      }

      if ( map_.getObject2( m ) != 0 )
      {
        bool isSelected = map_.getCharacterId( m ) == playerData_.getSelectedCharacter();
        copysprite( m, map_.getObject2( m ), map_.getLight( m ) | tmp, x * 32, y * 32, xoff + map_.getObjectXOffset( m ),
                    yoff + map_.getObjectYOffset( m ), map_.getLight( m ), MapSprite::SpriteType::Character, isSelected );
      }

      if ( playerData_.getAttackTarget() != 0 && playerData_.getAttackTarget() == map_.getCharacterId( m ) )
      {
        copysprite( m, 34, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ),
                    MapSprite::SpriteType::Unspecified );
      }

      if ( playerData_.getPlayerAction() == DR_GIVE && playerData_.getFirstTarget() == map_.getCharacterCrc( m ) )
      {
        copysprite( m, 45, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ),
                    MapSprite::SpriteType::Unspecified );
      }

      if ( ( playerData_.clientShouldShowNames() | playerData_.clientShouldShowPercentHealth() ) && map_.getCharacterId( m ) )
      {
        playerData_.set_look_proz( map_.getCharacterId( m ), map_.getCharacterCrc( m ), map_.getCharacterPercentHealth( m ) );

        // Draw player names and health percentages
        std::string stringToDraw = playerData_.lookup( map_.getCharacterId( m ), map_.getCharacterCrc( m ) );
        textToDraw_.emplace_back( stringToDraw, font_, FONT_SIZE );

        sf::Vector2i textPosition =
            dd_gputtext( x * 32, y * 32, stringToDraw, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ) );

        auto& lastText = *( textToDraw_.end() - 1 );

        // Look text that appears on the map
        lastText.setPosition( sf::Vector2f { static_cast< float >( textPosition.x ), static_cast< float >( textPosition.y ) } );
        lastText.setCharacterSize( 8 );
        lastText.setOutlineColor( sf::Color::Black );
        lastText.setOutlineThickness( 1.0f );
        lastText.setFillColor( MenAmongGods::MsgYellow );

        if ( MenAmongGods::ClientConfiguration::instance().enableHpBars() )
        {
          sf::RectangleShape healthBar {};
          healthBar.setPosition( sf::Vector2f { static_cast< float >( textPosition.x ), static_cast< float >( textPosition.y ) } +
                                 sf::Vector2f { 0.0, 10.0f } );

          // Calculate size based on health
          char proz = playerData_.get_proz( map_.getCharacterId( m ), map_.getCharacterCrc( m ) );

          if ( proz != 127 )
          {
            float healthScale = 30.0f * ( proz / 100.0f );
            healthBar.setSize( sf::Vector2f { healthScale, 1.0f } );
            healthBar.setFillColor( sf::Color::Red );
            healthBar.setOutlineColor( sf::Color::Black );
            healthBar.setOutlineThickness( 1.0f );

            healthBarsToDraw_.push_back( healthBar );
          }
        }
      }

      if ( playerData_.getPlayerAction() == DR_DROP && playerData_.getFirstTarget() == map_.getX( m ) &&
           playerData_.getSecondTarget() == map_.getY( m ) )
      {
        copysprite( m, 32, 0, x * 32, y * 32, xoff, yoff, 0, MapSprite::SpriteType::Unspecified );
      }
      if ( playerData_.getPlayerAction() == DR_PICKUP && playerData_.getFirstTarget() == map_.getX( m ) &&
           playerData_.getSecondTarget() == map_.getY( m ) )
      {
        copysprite( m, 33, 0, x * 32, y * 32, xoff, yoff, 0, MapSprite::SpriteType::Unspecified );
      }
      if ( playerData_.getPlayerAction() == DR_USE && playerData_.getFirstTarget() == map_.getX( m ) &&
           playerData_.getSecondTarget() == map_.getY( m ) )
      {
        copysprite( m, 45, 0, x * 32, y * 32, xoff, yoff, 0, MapSprite::SpriteType::Unspecified );
      }

      // effects
      if ( map_.getFlags2( m ) & MF_MOVEBLOCK )
      {
        copysprite( m, 55, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_SIGHTBLOCK )
      {
        copysprite( m, 84, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_INDOORS )
      {
        copysprite( m, 56, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_UWATER )
      {
        copysprite( m, 75, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_NOMONST )
      {
        copysprite( m, 59, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_BANK )
      {
        copysprite( m, 60, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_TAVERN )
      {
        copysprite( m, 61, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_NOMAGIC )
      {
        copysprite( m, 62, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_DEATHTRAP )
      {
        copysprite( m, 73, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_NOLAG )
      {
        copysprite( m, 57, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_ARENA )
      {
        copysprite( m, 76, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & MF_NOEXPIRE )
      {
        copysprite( m, 82, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }
      if ( map_.getFlags2( m ) & 0x80000000 )
      {
        copysprite( m, 72, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }

      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == INJURED )
      {
        copysprite( m, 1079, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ),
                    MapSprite::SpriteType::Unspecified );
      }
      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 ) )
      {
        copysprite( m, 1080, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ),
                    MapSprite::SpriteType::Unspecified );
      }
      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED2 ) )
      {
        copysprite( m, 1081, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ),
                    MapSprite::SpriteType::Unspecified );
      }
      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 | INJURED2 ) )
      {
        copysprite( m, 1082, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ),
                    MapSprite::SpriteType::Unspecified );
      }

      if ( map_.getFlags( m ) & DEATH )
      {
        if ( map_.getObject2( m ) )
        {
          copysprite( m, 280 + ( ( map_.getFlags( m ) & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ),
                      yoff + map_.getObjectYOffset( m ), map_.getLight( m ), MapSprite::SpriteType::Unspecified );
        }
        else
        {
          copysprite( m, 280 + ( ( map_.getFlags( m ) & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ),
                      MapSprite::SpriteType::Unspecified );
        }
      }
      if ( map_.getFlags( m ) & TOMB )
      {
        copysprite( m, 240 + ( ( map_.getFlags( m ) & TOMB ) >> 12 ) - 1, map_.getLight( m ), x * 32, y * 32, xoff, yoff,
                    map_.getLight( m ), MapSprite::SpriteType::Unspecified );
      }

      alpha    = 0;
      alphastr = 0;

      if ( map_.getFlags( m ) & EMAGIC )
      {
        alpha |= 1;
        alphastr              = std::max( ( unsigned ) alphastr, ( ( map_.getFlags( m ) & EMAGIC ) >> 22 ) );
        sf::Color emagicColor = sf::Color::Red;
        emagicColor.a         = 128;
        copyEffectSprite( m, 490 + alphastr, x * 32, y * 32, xoff, yoff, emagicColor );
      }

      if ( map_.getFlags( m ) & GMAGIC )
      {
        alpha |= 2;
        alphastr              = std::max( ( unsigned ) alphastr, ( ( map_.getFlags( m ) & GMAGIC ) >> 25 ) );
        sf::Color gmagicColor = sf::Color::Green;
        gmagicColor.a         = 128;
        copyEffectSprite( m, 490 + alphastr, x * 32, y * 32, xoff, yoff, gmagicColor );
      }

      if ( map_.getFlags( m ) & CMAGIC )
      {
        alpha |= 4;
        alphastr = std::max( ( unsigned ) alphastr, ( ( map_.getFlags( m ) & CMAGIC ) >> 28 ) );
        sf::Color cmagicColor { 128, 128, 128, 128 };
        copyEffectSprite( m, 490 + alphastr, x * 32, y * 32, xoff, yoff, cmagicColor );
      }
    }
  }

  if ( ! selected_visible )
  {
    playerData_.setSelectedCharacter( 0 );
  }

  sf::Vector2f mousePosition = getNormalizedMousePosition( window_ );

  playerData_.setHoverState( PlayerData::HoverState::NONE );

  // Add highlights at the end of the render loop to ensure they're always drawn last.  Effectively
  // what we're doing is copying the SAME sprite, putting in the SAME location, except changing to an additive blend
  // mode to get the highlight effect that we are looking for.  We use an if/else if chain to ensure
  // that we're only highlighting one thing at a time to mimic what is done when we issue commands to the server.
  if ( playerData_.isHoldingControl() )
  {
    auto mapIndices    = getFuzzyMapIndices( mousePosition );
    auto hoveredSprite = getSpriteByType( mapIndices, MapSprite::SpriteType::Character );

    if ( hoveredSprite != std::end( spritesToDraw_ ) )
    {
      MapSprite newSprite             = *hoveredSprite;
      lastHoveredIndex_               = hoveredSprite->index;
      newSprite.renderState.blendMode = sf::BlendAdd;
      spritesToDraw_.push_back( newSprite );

      if ( playerData_.getCarriedItem() == 0 )
      {
        playerData_.setHoverState( PlayerData::HoverState::ATTACK );
      }
      else
      {
        playerData_.setHoverState( PlayerData::HoverState::GIVE );
      }
    }
  }
  else if ( playerData_.isHoldingShift() )
  {
    auto mapIndices    = getFuzzyMapIndices( mousePosition );
    auto hoveredSprite = getSpriteByType( mapIndices, MapSprite::SpriteType::Object );

    // For interactable objects, we also need to check to ensure that the item is interactable
    if ( hoveredSprite != std::end( spritesToDraw_ ) &&
         ( ( map_.getFlags( hoveredSprite->index ) & ISITEM ) || ( map_.getFlags( hoveredSprite->index ) & ISUSABLE ) ) )
    {
      MapSprite newSprite             = *hoveredSprite;
      lastHoveredIndex_               = hoveredSprite->index;
      newSprite.renderState.blendMode = sf::BlendAdd;
      spritesToDraw_.push_back( newSprite );

      // Set the player's hover state appropriately
      playerData_.setHoverState( PlayerData::HoverState::USE );
    }
  }
  else
  {
    // Only need to check what is currently pointed at by the mouse cursor
    std::set< int > mapIndicesToCheck {};

    mapIndicesToCheck.insert( getMapIndexFromMousePosition( mousePosition ) );
    auto hoveredSprite = getSpriteByType( mapIndicesToCheck, MapSprite::SpriteType::Tile );

    if ( hoveredSprite != std::end( spritesToDraw_ ) )
    {
      MapSprite newSprite             = *hoveredSprite;
      newSprite.renderState.blendMode = sf::BlendAdd;
      spritesToDraw_.push_back( newSprite );
    }
  }
}

void MapDisplay::copyEffectSprite( int index, int nr, int xpos, int ypos, int xoff, int yoff, sf::Color effectColor )
{
  if ( nr == 0 )
  {
    return;
  }

  MapSprite newMapSprite { cache_.getSprite( nr ), index, MapSprite::SpriteType::Unspecified };
  spritesToDraw_.push_back( newMapSprite );
  sf::Sprite& newSprite = ( spritesToDraw_.end() - 1 )->sprite;

  if ( newSprite.getTexture() == nullptr )
  {
    return;
  }

  unsigned char xs = newSprite.getTexture()->getSize().x / 32;
  unsigned char ys = newSprite.getTexture()->getSize().y / 32;

  unsigned int rx = ( xpos / 2 ) + ( ypos / 2 ) - ( xs * 16 ) + 32 + XPOS - ( ( TILEX - 34 ) / 2 * 32 );
  if ( xpos < 0 && ( xpos & 1 ) )
  {
    rx--;
  }
  if ( ypos < 0 && ( ypos & 1 ) )
  {
    rx--;
  }

  unsigned int ry = ( xpos / 4 ) - ( ypos / 4 ) + YPOS - ys * 32;

  if ( xpos < 0 && ( xpos & 3 ) )
  {
    ry--;
  }
  if ( ypos < 0 && ( ypos & 3 ) )
  {
    ry++;
  }

  rx += xoff;
  ry += yoff;

  for ( unsigned int y = 0; y < 1; y++ )
  {
    for ( unsigned int x = 0; x < 1; x++ )
    {
      newSprite.setPosition( sf::Vector2f { static_cast< float >( rx + x * 32 ), static_cast< float >( ry + y * 32 ) } );
      newSprite.setColor( effectColor );
    }
  }
}

void MapDisplay::copysprite( int index, int nr, int effect, int xpos, int ypos, int xoff, int yoff, unsigned char light,
                             MapSprite::SpriteType spriteType, bool isCharacterSelected )
{
  if ( nr == 0 )
  {
    return;
  }

  // Player has exited, blacken all draw requests to an invalid sprite.
  if ( playerData_.getExitFlag() )
  {
    nr = 999;
  }

  MapSprite newMapSprite { cache_.getSprite( nr ), index, spriteType };
  spritesToDraw_.push_back( newMapSprite );
  sf::Sprite& newSprite = ( spritesToDraw_.end() - 1 )->sprite;

  if ( newSprite.getTexture() == nullptr )
  {
    return;
  }

  // xs / ys are the x and y size in tiles (width / 32), and height / 32 respectively
  auto newSpriteTexture = newSprite.getTexture();
  if ( newSpriteTexture == nullptr )
  {
    LOG_ERROR( "Attempting to copy sprite for null texture." );
    return;
  }

  unsigned char xs = newSprite.getTexture()->getSize().x / 32;
  unsigned char ys = newSprite.getTexture()->getSize().y / 32;

  unsigned int rx = ( xpos / 2 ) + ( ypos / 2 ) - ( xs * 16 ) + 32 + XPOS - ( ( TILEX - 34 ) / 2 * 32 );
  if ( xpos < 0 && ( xpos & 1 ) )
  {
    rx--;
  }
  if ( ypos < 0 && ( ypos & 1 ) )
  {
    rx--;
  }

  unsigned int ry = ( xpos / 4 ) - ( ypos / 4 ) + YPOS - ys * 32;

  if ( xpos < 0 && ( xpos & 3 ) )
  {
    ry--;
  }
  if ( ypos < 0 && ( ypos & 3 ) )
  {
    ry++;
  }

  rx += xoff;
  ry += yoff;

  sf::Vector2f spritePosition = sf::Vector2f { static_cast< float >( rx ), static_cast< float >( ry ) };
  cache_.correctPosition( nr, spritePosition );

  newSprite.setPosition( spritePosition );

  // Apply light effects
  // Light values range from 0 - 15
  std::uint8_t lightValue = 255u - static_cast< uint8_t >( static_cast< float >( light ) / 15.0f * 255u );
  newSprite.setColor( sf::Color { lightValue, lightValue, lightValue, 255u } );

  if ( effect & 64 )
  {
    newSprite.setColor( sf::Color { 0u, 0u, 0u, 0u } );
    effect -= 64;
  }

  if ( effect & 128 )
  {
    newSprite.setColor( sf::Color { 0u, 0u, 0u, 0u } );

    effect -= 128;
  }

  if ( isCharacterSelected )
  {
    newSprite.setColor( sf::Color::Green );
  }
}

} // namespace MenAmongGods