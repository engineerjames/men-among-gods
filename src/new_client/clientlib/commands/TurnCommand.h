#ifndef MEN_AMONG_GODS_TURN_COMMAND_H
#define MEN_AMONG_GODS_TURN_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class TurnCommand : public ClientCommand
{
public:
  TurnCommand( std::uint16_t x, std::uint32_t y );
  virtual ~TurnCommand() = default;

  virtual bool        send( sf::TcpSocket& socket ) const override;
  virtual Json::Value toJson() const override;

private:
  std::uint16_t x_;
  std::uint32_t y_;
};
} // namespace MenAmongGods

#endif