#ifndef MEN_AMONG_GODS_UNIQUE_COMMAND_H
#define MEN_AMONG_GODS_UNIQUE_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class UniqueCommand : public ClientCommand
{
public:
  UniqueCommand( std::int32_t unique1, std::int32_t unique2 );
  virtual ~UniqueCommand() = default;

  virtual bool        send( sf::TcpSocket& socket ) const override;
  virtual nlohmann::json toJson() const override;

private:
  std::int32_t unique1_;
  std::int32_t unique2_;
};
} // namespace MenAmongGods

#endif