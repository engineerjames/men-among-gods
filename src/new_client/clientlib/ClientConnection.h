#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <SFML/Network.hpp>
#include <array>
#include <cstdint>

#include "ClientCommand.h"
#include "ClientTypes.h"
#include "ConstantIdentifiers.h"

// Forward declarations
class TickBuffer;
class PlayerData;

class ClientConnection
{

public:
  enum struct SocketIOMode
  {
    NonBlocking,
    Blocking
  };

  ClientConnection( std::string hostIpAddress, unsigned short hostPort );
  ~ClientConnection();

  bool connect();
  bool login( PlayerData& playerData );
  bool sendPlayerData( const PlayerData& playerData );
  void setSocketMode( SocketIOMode newMode );
  void sendHardwareInfo();

  bool sendTick();
  bool receiveTick( TickBuffer& tickBuffer );

  std::string getMessageOfTheDay() const;
  void        processCommand( std::shared_ptr< MenAmongGods::ClientCommand > command );

private:
  enum struct ProcessStatus
  {
    CONTINUE = 0,
    DONE     = 1,
    ERROR    = -1
  };

  ProcessStatus processLoginResponse( PlayerData& playerData, const std::array< std::uint8_t, 16 >& buffer );
  void          say( const char* input );

  sf::TcpSocket                       clientSocket_;
  std::string                         hostIpAddress_;
  unsigned short                      hostPort_;
  bool                                isConnected_;
  int                                 unique1_;
  int                                 unique2_;
  int                                 serverVersion_;
  static const constexpr unsigned int VERSION = 0x020E06;
  // TODO: Re-evaluate where these members are used
  unsigned int            tickCount_;
  std::array< char, 256 > messageOfTheDay_;
};

#endif