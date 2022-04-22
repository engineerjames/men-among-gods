#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <array>
#include <memory>
#include <tuple>

#include "ClientTypes.h"
#include "Component.h"
#include "FontCache.h"
#include "Player.h"
#include "SkillTab.h"

#include <SFML/Graphics.hpp>

struct skilltab;

class PlayerData : public MenAmongGods::Component
{
public:
  PlayerData( const sf::RenderWindow& window, const MenAmongGods::FontCache& fontCache );
  ~PlayerData() = default;

  virtual void update() override;

  virtual void onUserInput( const sf::Event& e ) override;

  virtual void finalize() override;

  virtual void draw( sf::RenderTarget&, sf::RenderStates ) const;

  enum struct HoverState
  {
    USE,
    ATTACK,
    GIVE,
    DROP,
    PICKUP,
    NONE
  };

  struct LogMessage
  {
    LogType     type;
    std::string msg;

    LogMessage( LogType theType, const std::string& theMsg )
        : type( theType )
        , msg( theMsg )
    {
    }
  };

  typedef std::tuple< unsigned int, unsigned int > OkeyPasswordType;

  bool         hasPlayerDataChanged() const;
  const char*  getPlayerName() const;
  const char*  getPlayerDescription() const;
  std::uint8_t areWallsHidden() const;
  int          getPlayerDirection() const;
  sf::Vector2i getGotoPosition() const;
  int          getPlayerAction() const;
  int          getFirstTarget() const;
  int          getSecondTarget() const;
  int          clientShouldShowNames() const;
  int          clientShouldShowPercentHealth() const;
  int          getAttackTarget() const;
  int          getMode() const;
  void         setMode( int newMode );
  std::string  getRankString() const;
  int          getRank() const;
  void         setExitFlag( bool newValue );
  bool         getExitFlag() const;

  // TODO: Eliminate this series of "get" calls--need just a plethora of get/set commands
  // for the underlying data values so they can be properly protected from multi-threaded
  // collisions.
  cplayer&       getClientSidePlayerInfo();
  const cplayer& getClientSidePlayerInfo() const;
  look&          getLook();
  void           sortSkills();

  bool getShowLook() const;
  void setShowLook( bool shouldShowLook );
  void resetLookTimer();
  void incrementLookTimer();

  void           setXButton( xbutton button, int index );
  const xbutton& getXButton( int index );

  bool               getShouldShowShop() const;
  void               setShouldShowShop( bool shouldShowShop );
  void               setShopOnCurrentLook();
  look               getShop() const;
  std::vector< int > getUnknownCharacterIds() const;

  void saveToFile() const;
  void loadFromFile( const std::string& filePath );

  void saveToJsonFile( const std::string& fileName ) const;
  void loadFromJsonFile( const std::string& fileName );
  void fromJson( Json::Value& json );

  void         setName( std::string newName );
  void         setPassword( std::string password );
  void         setPassword( long unsigned int pass1, long unsigned int pass2 );
  void         setDescription( std::string description );
  void         setRaceAndSex( std::string race, std::string sex );
  void         setRaceAndSex( long unsigned int race );
  void         setUserNumber( long unsigned int usnr );
  void         setClientShouldShowNames( bool shouldShowNames );
  void         setClientShouldShowPercentHealth( bool shouldShowPercentHealth );
  void         setClientShouldHideWalls( bool shouldHideWalls );
  void         setOkeyName( char ( &pdataName )[ 40 ] );
  std::string  getOkeyName() const;
  unsigned int getOkeyUserNumber() const;
  int          getItem( int index ) const;
  int          getCarriedItem() const;
  void         setPlayerSprite( int spriteId );
  int          getPlayerSprite() const;

  void setUnique1( int newValue );
  void setUnique2( int newValue );
  int  getUnique1() const;
  int  getUnique2() const;

  void setSelectedCharacter( int characterId );
  int  getSelectedCharacter() const;

  int               getRaceAndSex() const;
  std::string       getPassword() const;
  OkeyPasswordType  getPasswordOkeyValues() const;
  long unsigned int getUserNumber() const;

  void                      addLogMessage( LogType type, const std::string& msg );
  std::vector< LogMessage > getAndClearLogMessages();

  void        set_look_proz( unsigned short nr, unsigned short id, int proz ) const;
  std::string lookup( int nr, unsigned short id ) const;
  void        add_look( unsigned short nr, char* name, unsigned short id );
  char        get_proz( int nr, unsigned short id ) const;

  void clear();

  bool isHoldingShift() const;
  bool isHoldingControl() const;

  void setHoverState( HoverState state );

private:
  // Holds the name, description, and some client-related settings (split apart later)
  const sf::RenderWindow&                  window_;
  const MenAmongGods::FontCache&           fontCache_;
  pdata                                    playerInfo_; // This is more what initially gets sent to the server
  bool                                     playerDataHasChanged_;
  cplayer                                  clientSidePlayerInfo_; // This is more the truth of what your character is...
  key                                      okey_;
  std::array< skilltab, MAX_SKILLS >       skillsList_;
  look                                     look_;
  std::string                              password_; // TODO: This is super insecure to store it like this long-term
  std::vector< LogMessage >                messages_;
  static std::map< unsigned short, looks > lookMap_;
  static int                               lookAt_;
  int                                      playerSprite_;
  int                                      selectedCharacter_;
  bool                                     shouldShowLook_;
  bool                                     shouldShowShop_;
  look                                     shop_;

  int unique1_;
  int unique2_;

  float lookTimer_;

  bool playerIsHoldingShift_;
  bool playerIsHoldingControl_;
  bool exitFlag_;

  HoverState hoverState_;
};

#endif