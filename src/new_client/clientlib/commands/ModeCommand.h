#ifndef MEN_AMONG_GODS_MODE_COMMAND_H
#define MEN_AMONG_GODS_MODE_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class ModeCommand : public ClientCommand
{
public:
  ModeCommand( std::uint16_t newMode );
  virtual ~ModeCommand() = default;

  virtual bool        send( sf::TcpSocket& socket ) const override;
  virtual Json::Value toJson() const override;

private:
  std::uint16_t newMode_;
};
} // namespace MenAmongGods

#endif