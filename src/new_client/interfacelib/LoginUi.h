#ifndef MEN_AMONG_GODS_LOGIN_UI_H
#define MEN_AMONG_GODS_LOGIN_UI_H

#include "ClientTypes.h"
#include "Component.h"
#include "LoadButtonDisplay.h"
#include "NewButtonDisplay.h"
#include "PasswordTextInputDisplay.h"
#include "RadioButtonDisplay.h"
#include "SaveButtonDisplay.h"
#include "SubmitButtonDisplay.h"
#include "TextInputDisplay.h"

#include <SFML/Graphics.hpp>

// Consider creating a radio button group class
#include <vector>

class PlayerData;

namespace MenAmongGods
{
class FontCache;

class LoginUi : public MenAmongGods::Component
{
public:
  LoginUi( PlayerData& playerData, const sf::RenderWindow& window, const FontCache& fontCache, unsigned int fontSize );
  ~LoginUi() = default;

  virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
  virtual void update() override;

  virtual void onUserInput( const sf::Event& e ) override;
  virtual void finalize() override;

  PlayerData& getPlayerData() const;
  bool        hasSubmitted() const;

private:
  void populatePlayerData() const;

  PlayerData& playerData_;

  sf::Text                          nameLabel_;
  TextInputDisplay                  nameEntry_;
  sf::Text                          descriptionLabel_;
  TextInputDisplay                  descriptionEntry_;
  sf::Text                          passwordLabel_;
  PasswordTextInputDisplay          passwordEntry_;
  std::vector< RadioButtonDisplay > raceSelection_;
  std::vector< RadioButtonDisplay > sexSelection_;
  SubmitButtonDisplay               submitButton_;
  SaveButtonDisplay                 saveButton_;
  LoadButtonDisplay                 loadButton_;
  NewButtonDisplay                  newButton_;

  std::vector< MenAmongGods::Component* > components_;
};
} // namespace MenAmongGods

#endif