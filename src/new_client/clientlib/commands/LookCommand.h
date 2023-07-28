#ifndef MEN_AMONG_GODS_LOOK_COMMAND_H
#define MEN_AMONG_GODS_LOOK_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class LookCommand : public ClientCommand
{
public:
  LookCommand( std::uint32_t characterNumber );
  virtual ~LookCommand() = default;

  virtual bool        send( sf::TcpSocket& socket ) const override;
  virtual nlohmann::json toJson() const override;

private:
  std::uint32_t characterNumber_;
};
} // namespace MenAmongGods

#endif