#ifndef MEN_AMONG_GODS_PASSWORD_COMMAND_H
#define MEN_AMONG_GODS_PASSWORD_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods // TODO: Still need to implement this class
{
class PasswordCommand : public ClientCommand
{
public:
  PasswordCommand( std::uint32_t passwordHash, std::uint32_t version, std::uint32_t raceAndSex );
  virtual ~PasswordCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::uint32_t passwordHash_;
  std::uint32_t version_;
  std::uint32_t raceAndSex_;
};
} // namespace MenAmongGods

#endif