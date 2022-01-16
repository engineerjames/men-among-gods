#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <SFML/Network.hpp>
#include <array>
#include <cstdint>

#include "ConstantIdentifiers.h"

class ClientConnection
{

public:
  ClientConnection( std::string hostIpAddress, unsigned short hostPort );
  ~ClientConnection();

  bool connect();

  bool login();

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
};

#endif