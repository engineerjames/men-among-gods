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
static const constexpr unsigned int HL_BUTTONBOX = 1;
static const constexpr unsigned int HL_STATBOX   = 2;
static const constexpr unsigned int HL_BACKPACK  = 3;
static const constexpr unsigned int HL_EQUIPMENT = 4;
static const constexpr unsigned int HL_SPELLBOX  = 5;
static const constexpr unsigned int HL_CITEM     = 6;
static const constexpr unsigned int HL_MONEY     = 7;
static const constexpr unsigned int HL_MAP       = 8;
static const constexpr unsigned int HL_SHOP      = 9;
static const constexpr unsigned int HL_STATBOX2  = 10;

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
  for ( const auto& tile : spritesToDraw_ )
  {
    target.draw( tile.sprite, states );
  }

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

    int m = getMapIndexFromMousePosition( mousePosition );

    for ( const auto& i : getFuzzyMapIndices( mousePosition ) )
    {
      cmap      clickedTile = map_.getMap( i );
      const int x           = clickedTile.x;
      const int y           = clickedTile.y;

      if ( x == 0 && y == 0 )
      {
        return;
      }

      if ( playerData_.getCarriedItem() != 0 && ! ( map_.getFlags( m ) & ISITEM ) )
      {
        commands_.emplace_back( std::make_shared< MenAmongGods::DropCommand >( x, y ) );
        return;
      }

      if ( map_.getFlags( m ) & ISITEM )
      {
        if ( map_.getFlags( m ) & ISUSABLE )
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
  int hightlight {};
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

      if ( hightlight == HL_MAP && tileType_ == 0 && tileX_ == x && tileY_ == y )
      {
        tmp = 16;
      }
      else
      {
        tmp = 0;
      }
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
      copysprite( m, map_.getBackgroundSprite( m ), map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );

      if ( playerData_.getGotoPosition().x == map_.getX( m ) && playerData_.getGotoPosition().y == map_.getY( m ) )
      {
        copysprite( m, 31, 0, x * 32, y * 32, xoff, yoff, 0 );
      }
    }
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

          if ( hightlight == HL_MAP && tileType_ == 1 && tileX_ == x && tileY_ == y )
          {
            copysprite( m, tmp2, map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
          }
          else
          {
            copysprite( m, tmp2, map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
          }
        }
        else
        {
          if ( hightlight == HL_MAP && tileType_ == 1 && tileX_ == x && tileY_ == y )
          {
            copysprite( m, map_.getObject1( m ), map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
          }
          else
          {
            copysprite( m, map_.getObject1( m ), map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
          }
        }
      }
      else if ( map_.getObject1( m ) )
      {
        copysprite( m, map_.getObject1( m ) + 1, map_.getLight( m ) | tmp, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
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
                    yoff + map_.getObjectYOffset( m ), map_.getLight( m ), isSelected );
      }

      if ( playerData_.getAttackTarget() != 0 && playerData_.getAttackTarget() == map_.getCharacterId( m ) )
      {
        copysprite( m, 34, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ) );
      }

      if ( playerData_.getPlayerAction() == DR_GIVE && playerData_.getFirstTarget() == map_.getCharacterCrc( m ) )
      {
        copysprite( m, 45, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ) );
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
        copysprite( m, 32, 0, x * 32, y * 32, xoff, yoff, 0 );
      }
      if ( playerData_.getPlayerAction() == DR_PICKUP && playerData_.getFirstTarget() == map_.getX( m ) &&
           playerData_.getSecondTarget() == map_.getY( m ) )
      {
        copysprite( m, 33, 0, x * 32, y * 32, xoff, yoff, 0 );
      }
      if ( playerData_.getPlayerAction() == DR_USE && playerData_.getFirstTarget() == map_.getX( m ) &&
           playerData_.getSecondTarget() == map_.getY( m ) )
      {
        copysprite( m, 45, 0, x * 32, y * 32, xoff, yoff, 0 );
      }

      // effects
      if ( map_.getFlags2( m ) & MF_MOVEBLOCK )
      {
        copysprite( m, 55, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_SIGHTBLOCK )
      {
        copysprite( m, 84, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_INDOORS )
      {
        copysprite( m, 56, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_UWATER )
      {
        copysprite( m, 75, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_NOMONST )
      {
        copysprite( m, 59, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_BANK )
      {
        copysprite( m, 60, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_TAVERN )
      {
        copysprite( m, 61, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_NOMAGIC )
      {
        copysprite( m, 62, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_DEATHTRAP )
      {
        copysprite( m, 73, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_NOLAG )
      {
        copysprite( m, 57, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_ARENA )
      {
        copysprite( m, 76, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & MF_NOEXPIRE )
      {
        copysprite( m, 82, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }
      if ( map_.getFlags2( m ) & 0x80000000 )
      {
        copysprite( m, 72, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
      }

      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == INJURED )
      {
        copysprite( m, 1079, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ) );
      }
      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 ) )
      {
        copysprite( m, 1080, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ) );
      }
      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED2 ) )
      {
        copysprite( m, 1081, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ) );
      }
      if ( ( map_.getFlags( m ) & ( INJURED | INJURED1 | INJURED2 ) ) == ( INJURED | INJURED1 | INJURED2 ) )
      {
        copysprite( m, 1082, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ), yoff + map_.getObjectYOffset( m ), map_.getLight( m ) );
      }

      if ( map_.getFlags( m ) & DEATH )
      {
        if ( map_.getObject2( m ) )
        {
          copysprite( m, 280 + ( ( map_.getFlags( m ) & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff + map_.getObjectXOffset( m ),
                      yoff + map_.getObjectYOffset( m ), map_.getLight( m ) );
        }
        else
        {
          copysprite( m, 280 + ( ( map_.getFlags( m ) & DEATH ) >> 17 ) - 1, 0, x * 32, y * 32, xoff, yoff, map_.getLight( m ) );
        }
      }
      if ( map_.getFlags( m ) & TOMB )
      {
        copysprite( m, 240 + ( ( map_.getFlags( m ) & TOMB ) >> 12 ) - 1, map_.getLight( m ), x * 32, y * 32, xoff, yoff,
                    map_.getLight( m ) );
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

  int mapIndex = getMapIndexFromMousePosition( mousePosition );

  auto hoveredSprite = std::find_if( std::begin( spritesToDraw_ ), std::end( spritesToDraw_ ),
                                     [ & ]( const MapSprite& mapSprite )
                                     {
                                       return mapIndex == mapSprite.index;
                                     } );

  if ( hoveredSprite != std::end( spritesToDraw_ ) )
  {
    hoveredSprite->sprite.setColor( sf::Color { 128, 128, 128, 255 } );
  }
}

void MapDisplay::copyEffectSprite( int index, int nr, int xpos, int ypos, int xoff, int yoff, sf::Color effectColor )
{
  if ( nr == 0 )
  {
    return;
  }

  MapSprite newMapSprite { cache_.getSprite( nr ), index };
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
                             bool isCharacterSelected )
{
  if ( nr == 0 )
  {
    return;
  }

  MapSprite newMapSprite { cache_.getSprite( nr ), index };
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