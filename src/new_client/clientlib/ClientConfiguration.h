#ifndef MEN_AMONG_GODS_CLIENT_CONFIGURATION_H
#define MEN_AMONG_GODS_CLIENT_CONFIGURATION_H

#include <string>

#include "Logger.h"

namespace MenAmongGods
{
class ClientConfiguration
{
public:
  static ClientConfiguration instance();

  int         networkThreadDelay() const;
  int         frameLimit() const;
  bool        loggingEnabled() const;
  std::string hostIpAddress() const;
  int         hostPort() const;
  bool        enableHpBars() const;

  nlohmann::json toJson() const;

private:
  ClientConfiguration();

  int         networkThreadDelay_;
  int         frameLimit_;
  bool        loggingEnabled_;
  std::string hostIpAddress_;
  int         hostPort_;
  bool        enableHpBars_;
};
} // namespace MenAmongGods

#endif