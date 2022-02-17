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

  int         networkThreadDelay();
  int         frameLimit();
  Json::Value toJson() const;

private:
  ClientConfiguration();

  int networkThreadDelay_;
  int frameLimit_;
};
} // namespace MenAmongGods

#endif