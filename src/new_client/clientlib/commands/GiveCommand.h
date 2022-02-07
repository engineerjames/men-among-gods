#ifndef MEN_AMONG_GODS_GIVE_COMMAND_H
#define MEN_AMONG_GODS_GIVE_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class GiveCommand : public ClientCommand
{
public:
  GiveCommand( std::uint32_t characterNumber );
  virtual ~GiveCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::uint32_t characterNumber_;
};
} // namespace MenAmongGods

#endif