#ifndef MEN_AMONG_GODS_USE_COMMAND_H
#define MEN_AMONG_GODS_USE_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class UseCommand : public ClientCommand< ClientMessages::MessageTypes, ClientMessages::MessageTypes::CMD_USE >
{
public:
  UseCommand( std::uint16_t x, std::uint32_t y );
  virtual ~UseCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::uint16_t x_;
  std::uint32_t y_;
};
} // namespace MenAmongGods

#endif