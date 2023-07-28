#ifndef MEN_AMONG_GODS_PASSWORD_COMMAND_H
#define MEN_AMONG_GODS_PASSWORD_COMMAND_H

#include "ClientCommand.h"

#include <string>

namespace MenAmongGods
{
class PasswordCommand : public ClientCommand
{
public:
  PasswordCommand( const std::string& password );
  virtual ~PasswordCommand() = default;

  virtual bool        send( sf::TcpSocket& socket ) const override;
  virtual nlohmann::json toJson() const override;

private:
  std::string password_;
};
} // namespace MenAmongGods

#endif