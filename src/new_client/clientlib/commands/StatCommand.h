#ifndef MEN_AMONG_GODS_STAT_COMMAND_H
#define MEN_AMONG_GODS_STAT_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class StatCommand : public ClientCommand< ClientMessages::MessageTypes, ClientMessages::MessageTypes::CMD_STAT >
{
public:
  StatCommand( std::uint16_t x, std::uint32_t y ); // TODO: Figure out what these numbers represent
  virtual ~StatCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::uint16_t x_;
  std::uint32_t y_;
};
} // namespace MenAmongGods

#endif