#ifndef MEN_AMONG_GODS_NEW_LOGIN_COMMAND_H
#define MEN_AMONG_GODS_NEW_LOGIN_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class NewLoginCommand : public ClientCommand
{
public:
  NewLoginCommand();
  virtual ~NewLoginCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  // Nothing for now
};
} // namespace MenAmongGods

#endif