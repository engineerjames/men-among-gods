#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <SFML/Network.hpp>
#include <array>
#include <cstdint>

class ClientConnection
{

public:
  ClientConnection( std::string hostIpAddress, unsigned short hostPort );
  ~ClientConnection();

  bool connect();

  bool login();

private:
  bool processLoginResponse( const std::array< std::uint8_t, 16 > &buffer );

  sf::TcpSocket  clientSocket_;
  std::string    hostIpAddress_;
  unsigned short hostPort_;
  bool           isConnected_;
  int            unique1_;
  int            unique2_;

  static const constexpr unsigned int VERSION = 0x020E06;
};

#endif