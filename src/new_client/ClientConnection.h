#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <SFML/Network.hpp>
#include <array>
#include <cstdint>

#include "ConstantIdentifiers.h"

// Forward declarations
class TickBuffer;

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
  bool login();
  bool sendPlayerData( const pdata &playerData );
  void setSocketMode(SocketIOMode newMode);

  bool sendTick();
  bool receiveTick( TickBuffer &tickBuffer );

private:
  enum struct ProcessStatus
  {
    CONTINUE = 0,
    DONE     = 1,
    ERROR    = -1
  };

  ProcessStatus processLoginResponse( const std::array< std::uint8_t, 16 > &buffer );

  sf::TcpSocket                       clientSocket_;
  std::string                         hostIpAddress_;
  unsigned short                      hostPort_;
  bool                                isConnected_;
  int                                 unique1_;
  int                                 unique2_;
  int                                 serverVersion_;
  key                                 clientData_;
  static const constexpr unsigned int VERSION = 0x020E06;
  // TODO: Re-evaluate where these members are used
  unsigned int tickCount_;
};

#endif