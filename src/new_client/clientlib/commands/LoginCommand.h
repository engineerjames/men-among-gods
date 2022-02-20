#ifndef MEN_AMONG_GODS_LOGIN_COMMAND_H
#define MEN_AMONG_GODS_LOGIN_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class LoginCommand : public ClientCommand
{
public:
  LoginCommand( std::uint32_t userNumber, std::uint32_t password1, std::uint32_t password2 );
  virtual ~LoginCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::uint32_t userNumber_;
  std::uint32_t password1_;
  std::uint32_t password2_;
};
} // namespace MenAmongGods

#endif