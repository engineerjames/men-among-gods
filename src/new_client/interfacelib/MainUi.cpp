#include "MainUi.h"

#include "ColorPalette.h"
#include "ConstantIdentifiers.h"
#include "FontCache.h"
#include "GraphicsCache.h"
#include "GuiFormatters.h"
#include "PlayerData.h"
#include "UiPositions.h"

namespace MenAmongGods
{

MainUi::MainUi( const sf::RenderWindow& window, Map& map, PlayerData& pdata, const GraphicsCache& gfxCache, const GraphicsIndex& gfxIndex,
                const FontCache& fontCache )
    : MenAmongGods::Component()
    , playerData_( pdata )
    , font_( fontCache.getFont() )
    , goldDisplay_()
    , avLabel_()
    , avValue_()
    , wvLabel_()
    , wvValue_()
    , expLabel_()
    , expValue_()
    , skillsAndAttributes_( window, font_, gfxCache, gfxIndex, pdata )
    , lifeDisplay_( font_, pdata )
    , msgBox_()
    , userInput_( font_ )
    , playerEquipment_( pdata, gfxCache )
    , playerInventory_( pdata, gfxCache )
    , userOptionPanel_( window, pdata )
    , mapDisplay_( font_, map, pdata, gfxCache, gfxIndex, window )
    , rankDisplay_( font_, pdata, gfxCache )
    , background_()
{
  goldDisplay_.setPosition( MenAmongGods::goldDisplayPosition );
  userInput_.setPosition( MenAmongGods::userInputPosition );

  avLabel_.setPosition( MenAmongGods::avLabelPosition );
  avValue_.setPosition( MenAmongGods::avValuePosition );

  wvLabel_.setPosition( MenAmongGods::wvLabelPosition );
  wvValue_.setPosition( MenAmongGods::wvValuePosition );

  expLabel_.setPosition( MenAmongGods::expLabelPosition );
  expValue_.setPosition( MenAmongGods::expValuePosition );

  hpLabel_.setPosition( MenAmongGods::hpLabelPosition );
  hpCurrentValue_.setPosition( MenAmongGods::hpCurrentValuePosition );
  hpMaxValue_.setPosition( MenAmongGods::hpMaxValuePosition );

  endLabel_.setPosition( MenAmongGods::endLabelPosition );
  endCurrentValue_.setPosition( MenAmongGods::endCurrentValuePosition );
  endMaxValue_.setPosition( MenAmongGods::endMaxValuePosition );

  manaLabel_.setPosition( MenAmongGods::manaLabelPosition );
  manaCurrentValue_.setPosition( MenAmongGods::manaCurrentValuePosition );
  manaMaxValue_.setPosition( MenAmongGods::manaMaxValuePosition );

  goldDisplay_.setFont( font_ );
  avLabel_.setFont( font_ );
  avValue_.setFont( font_ );
  wvLabel_.setFont( font_ );
  wvValue_.setFont( font_ );
  expLabel_.setFont( font_ );
  expValue_.setFont( font_ );
  hpLabel_.setFont( font_ );
  hpCurrentValue_.setFont( font_ );
  hpMaxValue_.setFont( font_ );
  endLabel_.setFont( font_ );
  endCurrentValue_.setFont( font_ );
  endMaxValue_.setFont( font_ );
  manaLabel_.setFont( font_ );
  manaCurrentValue_.setFont( font_ );
  manaMaxValue_.setFont( font_ );

  goldDisplay_.setCharacterSize( FONT_SIZE );
  avLabel_.setCharacterSize( FONT_SIZE );
  avValue_.setCharacterSize( FONT_SIZE );
  wvLabel_.setCharacterSize( FONT_SIZE );
  wvValue_.setCharacterSize( FONT_SIZE );
  expLabel_.setCharacterSize( FONT_SIZE );
  expValue_.setCharacterSize( FONT_SIZE );
  hpLabel_.setCharacterSize( FONT_SIZE );
  hpCurrentValue_.setCharacterSize( FONT_SIZE );
  hpMaxValue_.setCharacterSize( FONT_SIZE );
  endLabel_.setCharacterSize( FONT_SIZE );
  endCurrentValue_.setCharacterSize( FONT_SIZE );
  endMaxValue_.setCharacterSize( FONT_SIZE );
  manaLabel_.setCharacterSize( FONT_SIZE );
  manaCurrentValue_.setCharacterSize( FONT_SIZE );
  manaMaxValue_.setCharacterSize( FONT_SIZE );

  goldDisplay_.setFillColor( MenAmongGods::MsgYellow );
  avLabel_.setFillColor( MenAmongGods::MsgYellow );
  avValue_.setFillColor( MenAmongGods::MsgYellow );
  wvLabel_.setFillColor( MenAmongGods::MsgYellow );
  wvValue_.setFillColor( MenAmongGods::MsgYellow );
  expLabel_.setFillColor( MenAmongGods::MsgYellow );
  expValue_.setFillColor( MenAmongGods::MsgYellow );
  hpLabel_.setFillColor( MenAmongGods::MsgYellow );
  hpCurrentValue_.setFillColor( MenAmongGods::MsgYellow );
  hpMaxValue_.setFillColor( MenAmongGods::MsgYellow );
  endLabel_.setFillColor( MenAmongGods::MsgYellow );
  endCurrentValue_.setFillColor( MenAmongGods::MsgYellow );
  endMaxValue_.setFillColor( MenAmongGods::MsgYellow );
  manaLabel_.setFillColor( MenAmongGods::MsgYellow );
  manaCurrentValue_.setFillColor( MenAmongGods::MsgYellow );
  manaMaxValue_.setFillColor( MenAmongGods::MsgYellow );

  goldDisplay_.setOutlineColor( sf::Color::Black );
  avLabel_.setOutlineColor( sf::Color::Black );
  avValue_.setOutlineColor( sf::Color::Black );
  wvLabel_.setOutlineColor( sf::Color::Black );
  wvValue_.setOutlineColor( sf::Color::Black );
  expLabel_.setOutlineColor( sf::Color::Black );
  expValue_.setOutlineColor( sf::Color::Black );
  hpLabel_.setOutlineColor( sf::Color::Black );
  hpCurrentValue_.setOutlineColor( sf::Color::Black );
  hpMaxValue_.setOutlineColor( sf::Color::Black );
  endLabel_.setOutlineColor( sf::Color::Black );
  endCurrentValue_.setOutlineColor( sf::Color::Black );
  endMaxValue_.setOutlineColor( sf::Color::Black );
  manaLabel_.setOutlineColor( sf::Color::Black );
  manaCurrentValue_.setOutlineColor( sf::Color::Black );
  manaMaxValue_.setOutlineColor( sf::Color::Black );

  goldDisplay_.setString( "5g 52s" );
  avLabel_.setString( "Armor Value" );
  avValue_.setString( "0" );
  wvLabel_.setString( "Weapon Value" );
  wvValue_.setString( "0" );
  expLabel_.setString( "Experience" );
  expValue_.setString( MenAmongGods::addThousandsSeparator( 12412125u ) );
  hpLabel_.setString( "Hitpoints" );
  hpCurrentValue_.setString( "100" );
  hpMaxValue_.setString( "100" );
  endLabel_.setString( "Endurance" );
  endCurrentValue_.setString( "100" );
  endMaxValue_.setString( "100" );
  manaLabel_.setString( "Mana" );
  manaCurrentValue_.setString( "100" );
  manaMaxValue_.setString( "100" );

  wvValue_.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );
  avValue_.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );
  expValue_.setJustification( MenAmongGods::JustifiableText::TextJustification::RIGHT );

  background_ = gfxCache.getSprite( 1 );
  background_.setPosition( sf::Vector2f { 0.0f, 0.0f } );
}

void MainUi::addMessage( LogType type, std::string text )
{
  sf::Text  newMsg { text, font_, static_cast< unsigned int >( FONT_SIZE ) };
  sf::Color messageColor {};

  switch ( type )
  {
  case LogType::CHAT:
    messageColor = MenAmongGods::MsgBlue;
    break;
  case LogType::LOG:
    messageColor = MenAmongGods::MsgGreen;
    break;
  case LogType::ERROR:
    messageColor = MenAmongGods::MsgRed;
    break;
  case LogType::INFO:
    messageColor = MenAmongGods::MsgYellow;
    break;
  default:
    messageColor = sf::Color::Blue;
    break;
  }

  newMsg.setFillColor( messageColor );
  newMsg.setOutlineColor( sf::Color::Black );
  newMsg.setLetterSpacing( LETTER_SPACING );

  msgBox_.addMessage( newMsg );
}

void MainUi::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( mapDisplay_, states );

  // Draw the background first
  target.draw( background_, states );

  target.draw( rankDisplay_, states );
  target.draw( goldDisplay_, states );
  target.draw( msgBox_, states );
  target.draw( userInput_, states );
  target.draw( avLabel_, states );
  target.draw( avValue_, states );
  target.draw( wvLabel_, states );
  target.draw( wvValue_, states );
  target.draw( expLabel_, states );
  target.draw( expValue_, states );
  target.draw( hpLabel_, states );
  target.draw( hpCurrentValue_, states );
  target.draw( hpMaxValue_, states );
  target.draw( endLabel_, states );
  target.draw( endCurrentValue_, states );
  target.draw( endMaxValue_, states );
  target.draw( manaLabel_, states );
  target.draw( manaCurrentValue_, states );
  target.draw( manaMaxValue_, states );
  target.draw( skillsAndAttributes_, states );
  target.draw( lifeDisplay_, states );
  target.draw( playerEquipment_, states );
  target.draw( playerInventory_, states );
  target.draw( userOptionPanel_, states );
}

void MainUi::onUserInput( const sf::Event& e )
{
  rankDisplay_.onUserInput( e );
  mapDisplay_.onUserInput( e );
  userInput_.onUserInput( e );
  skillsAndAttributes_.onUserInput( e );
  lifeDisplay_.onUserInput( e );
  playerEquipment_.onUserInput( e );
  playerInventory_.onUserInput( e );
  userOptionPanel_.onUserInput( e );
}

void MainUi::update()
{
  playerData_.lock();

  mapDisplay_.update();
  rankDisplay_.update();

  // Update UI from player data
  cplayer& player = playerData_.getClientSidePlayerInfo();
  avValue_.setString( std::to_string( player.armor ) );
  wvValue_.setString( std::to_string( player.weapon ) );
  hpCurrentValue_.setString( std::to_string( player.a_hp ) );
  endCurrentValue_.setString( std::to_string( player.a_end ) );
  manaCurrentValue_.setString( std::to_string( player.a_mana ) );

  // TODO: This has to be wrong--does a_* represent the max or current
  // values?
  hpMaxValue_.setString( std::to_string( player.a_hp ) );
  endMaxValue_.setString( std::to_string( player.a_end ) );
  manaMaxValue_.setString( std::to_string( player.a_mana ) );

  goldDisplay_.setString( MenAmongGods::goldToString( player.gold ) );

  expValue_.setString( std::to_string( player.points_tot ) );

  skillsAndAttributes_.update();

  lifeDisplay_.update();

  playerEquipment_.update();

  playerInventory_.update();

  // TODO: Fix naming consistency (user vs. client, vs. player)
  userOptionPanel_.update();

  // Update JustifiableText
  wvValue_.update();
  avValue_.update();
  expValue_.update();

  // Get new message values
  for ( const auto& m : playerData_.getAndClearLogMessages() )
  {
    addMessage( m.type, m.msg );
  }

  playerData_.unlock();
}

void MainUi::populateCommands( std::vector< std::shared_ptr< ClientCommand > >& outCommands )
{
  rankDisplay_.populateCommands( outCommands );
  mapDisplay_.populateCommands( outCommands );
  userInput_.populateCommands( outCommands );
  skillsAndAttributes_.populateCommands( outCommands );
  lifeDisplay_.populateCommands( outCommands );
  msgBox_.populateCommands( outCommands );
  playerEquipment_.populateCommands( outCommands );
  playerInventory_.populateCommands( outCommands );
}

void MainUi::finalize()
{
  rankDisplay_.finalize();
  mapDisplay_.finalize();
  userInput_.finalize();
  msgBox_.finalize();
  lifeDisplay_.finalize();
  playerEquipment_.finalize();
  playerInventory_.finalize();
  wvValue_.finalize();
  avValue_.finalize();
  expValue_.finalize();
  userOptionPanel_.finalize();
}
} // namespace MenAmongGods