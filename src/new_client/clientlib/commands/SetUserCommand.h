#ifndef MEN_AMONG_GODS_SET_USER_COMMAND_H
#define MEN_AMONG_GODS_SET_USER_COMMAND_H

#include "ClientCommand.h"

#include <array>

namespace MenAmongGods
{
class SetUserCommand : public ClientCommand
{
public:
  SetUserCommand( const std::string& playerName, const std::string& playerDescription );
  virtual ~SetUserCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::string playerName_;
  std::string playerDescription_;
};
} // namespace MenAmongGods

#endif