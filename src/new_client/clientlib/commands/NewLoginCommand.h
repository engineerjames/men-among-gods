#ifndef MEN_AMONG_GODS_NEW_LOGIN_COMMAND_H
#define MEN_AMONG_GODS_NEW_LOGIN_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods // TODO: Still need to implement this class
{
class NewLoginCommand : public ClientCommand< ClientMessages::MessageTypes, ClientMessages::MessageTypes::NEWLOGIN >
{
public:
  NewLoginCommand( std::uint32_t newloginHash, std::uint32_t version, std::uint32_t raceAndSex );
  virtual ~NewLoginCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::uint32_t newloginHash_;
  std::uint32_t version_;
  std::uint32_t raceAndSex_;
};
} // namespace MenAmongGods

#endif