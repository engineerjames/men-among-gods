#include "LoginUi.h"

#include <string.h>

#include "FontCache.h"
#include "PlayerData.h"

namespace MenAmongGods
{
LoginUi::LoginUi( PlayerData& playerData, const sf::RenderWindow& window, const FontCache& fontCache, unsigned int fontSize )
    : MenAmongGods::Component()
    , playerData_( playerData )
    , nameLabel_( "Name:", fontCache.getFont(), fontSize )
    , nameEntry_( window, fontCache.getFont(), fontSize )
    , descriptionLabel_( "Description:", fontCache.getFont(), fontSize )
    , descriptionEntry_( window, fontCache.getFont(), fontSize )
    , passwordLabel_( "Password:", fontCache.getFont(), fontSize )
    , passwordEntry_( window, fontCache.getFont(), fontSize )
    , raceSelection_()
    , sexSelection_()
    , submitButton_( window, fontCache.getFont(), fontSize, sf::Vector2f { 75, 50 } )
    , saveButton_( window, playerData, fontCache.getFont(), fontSize, sf::Vector2f { 75, 50 } )
    , loadButton_( window, playerData, fontCache.getFont(), fontSize, sf::Vector2f { 75, 50 } )
    , newButton_( window, playerData, fontCache.getFont(), fontSize, sf::Vector2f { 75, 50 } )
    , components_()
{
  raceSelection_.emplace_back( window, fontCache.getFont(), "Harakim", 10.0f, fontSize );
  raceSelection_.emplace_back( window, fontCache.getFont(), "Templar", 10.0f, fontSize );
  raceSelection_.emplace_back( window, fontCache.getFont(), "Mercenary", 10.0f, fontSize );

  raceSelection_[ 0 ].setPosition( sf::Vector2f { 500.0f, 10.0f } );
  raceSelection_[ 1 ].setPosition( sf::Vector2f { 500.0f, 60.0f } );
  raceSelection_[ 2 ].setPosition( sf::Vector2f { 500.0f, 110.0f } );

  sexSelection_.emplace_back( window, fontCache.getFont(), "Male", 10.0f, fontSize );
  sexSelection_.emplace_back( window, fontCache.getFont(), "Female", 10.0f, fontSize );

  sexSelection_[ 0 ].setPosition( sf::Vector2f { 500.0f, 200.0f } );
  sexSelection_[ 1 ].setPosition( sf::Vector2f { 500.0f, 250.0f } );

  // Set the Name and Description Boxes
  nameLabel_.setPosition( sf::Vector2f { 10.0f, 10.0f } );
  nameEntry_.setPosition( sf::Vector2f { 10.0f, 35.0f } );
  passwordLabel_.setPosition( sf::Vector2f { 10.0f, 60.0f } );
  passwordEntry_.setPosition( sf::Vector2f { 10.0f, 85.0f } );
  descriptionLabel_.setPosition( sf::Vector2f { 10.0f, 115.0f } );
  descriptionEntry_.setPosition( sf::Vector2f { 10.0f, 140.0f } );

  // Set up the submit button
  auto callBack = [ this ]()
  {
    this->populatePlayerData();
  };

  // Set up the new button callback
  auto newCallback = [ this ]()
  {
    nameEntry_.setText( "" );
    passwordEntry_.setText( "" );

    for ( auto& r : raceSelection_ )
    {
      r.setSelected( false );
    }

    for ( auto& s : sexSelection_ )
    {
      s.setSelected( false );
    }
  };

  submitButton_.setPosition( sf::Vector2f { 10.0f, 200.0f } );
  submitButton_.setCallBack( callBack );

  saveButton_.setPosition( sf::Vector2f { 125.0f, 200.0f } );

  loadButton_.setPosition( sf::Vector2f { 240.0f, 200.0f } );

  newButton_.setPosition( sf::Vector2f { 10.0f, 275.0f } );
  newButton_.setCallBack( newCallback );

  // Register components
  components_.push_back( &nameEntry_ );
  components_.push_back( &descriptionEntry_ );
  components_.push_back( &passwordEntry_ );
  components_.push_back( &submitButton_ );
  components_.push_back( &saveButton_ );
  components_.push_back( &loadButton_ );
  components_.push_back( &newButton_ );

  for ( auto& r : raceSelection_ )
  {
    components_.push_back( &r );
  }

  for ( auto& s : sexSelection_ )
  {
    components_.push_back( &s );
  }
}

bool LoginUi::hasSubmitted() const
{
  return submitButton_.hasSubmitted();
}

void LoginUi::update()
{
  static bool hasLoadedFile = false;
  if ( ! hasSubmitted() && ! hasLoadedFile && playerData_.getOkeyUserNumber() != 0 )
  {
    hasLoadedFile = true;

    // Load file details into UI elements.  This is super stupid but we can refactor later.
    std::string playerName = playerData_.getPlayerName();

    if ( playerName.empty() )
    {
      playerName = playerData_.getClientSidePlayerInfo().name;

      if ( playerName.empty())
      {
        playerName = playerData_.getOkeyName();
      }
    }

    nameEntry_.setText( playerName );
    descriptionEntry_.setText( playerData_.getPlayerDescription() );

    // Set race and sex
    int raceAndSex     = playerData_.getRaceAndSex();
    auto [ race, sex ] = getRaceAndSexFromInt( raceAndSex );

    if ( sex == MenAmongGods::Sex::Female )
    {
      sexSelection_[ 1 ].setSelected( true );
    }
    else
    {
      sexSelection_[ 0 ].setSelected( true );
    }

    if ( race == MenAmongGods::Race::Harakim )
    {
      raceSelection_[ 0 ].setSelected( true );
    }
    else if ( race == MenAmongGods::Race::Templar )
    {
      raceSelection_[ 1 ].setSelected( true );
    }
    else if ( race == MenAmongGods::Race::Mercenary )
    {
      raceSelection_[ 2 ].setSelected( true );
    }
  }

  for ( auto& c : components_ )
  {
    c->update();
  }
}

void LoginUi::onUserInput( const sf::Event& e )
{
  for ( auto& c : components_ )
  {
    c->onUserInput( e );
  }
}

void LoginUi::finalize()
{
  for ( auto& c : components_ )
  {
    c->finalize();
  }
}

void LoginUi::populatePlayerData() const
{
  playerData_.setName( nameEntry_.getText() );
  playerData_.setPassword( passwordEntry_.getText() );
  playerData_.setDescription( descriptionEntry_.getText() );

  std::string race {};
  for ( const auto& r : raceSelection_ )
  {
    if ( r.isSelected() )
    {
      race = r.getLabelText();
      break;
    }
  }

  std::string sex {};
  for ( const auto& s : sexSelection_ )
  {
    if ( s.isSelected() )
    {
      sex = s.getLabelText();
      break;
    }
  }

  playerData_.setRaceAndSex( race, sex );
}

PlayerData& LoginUi::getPlayerData() const
{
  return playerData_;
}

void LoginUi::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  target.draw( nameLabel_, states );
  target.draw( descriptionLabel_, states );
  target.draw( passwordLabel_, states );

  for ( auto& c : components_ )
  {
    target.draw( *c, states );
  }
}

} // namespace MenAmongGods