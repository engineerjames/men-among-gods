#ifndef MEN_AMONG_GODS_AUTO_LOOK_COMMAND_H
#define MEN_AMONG_GODS_AUTO_LOOK_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class AutoLookCommand : public ClientCommand< CommandType, CommandType::CL_CMD_AUTOLOOK >
{
public:
  AutoLookCommand( std::uint32_t characterNumber );
  virtual ~AutoLookCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::uint32_t characterNumber_;
};
} // namespace MenAmongGods

#endif