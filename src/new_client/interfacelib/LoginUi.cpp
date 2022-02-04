#include "LoginUi.h"

#include <iostream>
#include <string.h>

#include "FontCache.h"
#include "PlayerData.h"

namespace MenAmongGods
{
LoginUi::LoginUi( PlayerData& playerData, const sf::RenderWindow& window, const FontCache& fontCache, unsigned int fontSize )
    : playerData_( playerData )
    , nameLabel_( "Name:", fontCache.getFont(), fontSize )
    , nameEntry_( window, fontCache.getFont(), fontSize )
    , descriptionLabel_( "Description:", fontCache.getFont(), fontSize )
    , descriptionEntry_( window, fontCache.getFont(), fontSize )
    , passwordLabel_( "Password:", fontCache.getFont(), fontSize )
    , passwordEntry_( window, fontCache.getFont(), fontSize )
    , raceSelection_()
    , sexSelection_()
    , submitButton_( window, fontCache.getFont(), fontSize, sf::Vector2f { 75, 50 } )
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

  submitButton_.setPosition( sf::Vector2f { 10.0f, 200.0f } );
  submitButton_.setCallBack( callBack );

  // Register components
  components_.push_back( &nameEntry_ );
  components_.push_back( &descriptionEntry_ );
  components_.push_back( &passwordEntry_ );
  components_.push_back( &submitButton_ );

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

  printValues();
}

void LoginUi::printValues() const
{
  std::cerr << "Name: " << nameEntry_.getText() << std::endl;
  std::cerr << "Password: " << passwordEntry_.getText() << std::endl;
  std::cerr << "Description: " << descriptionEntry_.getText() << std::endl;

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

  std::cerr << "Race: " << race << std::endl;
  std::cerr << "Sex: " << sex << std::endl;
}

pdata LoginUi::getPlayerData() const
{
  pdata data {};

  strcpy( data.cname, nameEntry_.getText().c_str() );
  strcpy( data.desc, descriptionEntry_.getText().c_str() );

  data.show_proz = 0;
  data.hide      = 1;

  return data;
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