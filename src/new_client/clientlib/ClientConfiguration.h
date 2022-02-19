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
  Json::Value toJson() const;

private:
  ClientConfiguration();

  int  networkThreadDelay_;
  int  frameLimit_;
  bool loggingEnabled_;
};
} // namespace MenAmongGods

#endif