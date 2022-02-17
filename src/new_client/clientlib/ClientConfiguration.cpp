#include "ClientConfiguration.h"

#include "ResourceLocations.h"

#include <fstream>
#include <json/json.h>

namespace MenAmongGods
{
ClientConfiguration ClientConfiguration::instance()
{
  static ClientConfiguration instance_ {};

  // Read in the JSON parameters from the file
  std::ifstream inputJsonFile { MenAmongGods::getConfigPath() + "config.json" };
  Json::Value   root {};

  inputJsonFile >> root;

  instance_.networkThreadDelay_ = root.get( "networkThreadDelay", instance_.networkThreadDelay_ ).asInt();
  instance_.frameLimit_         = root.get( "frameLimit", instance_.frameLimit_ ).asInt();

  LOG_DEBUG_OBJ( instance_, "Client configuration parameters" );

  return instance_;
}

Json::Value ClientConfiguration::toJson() const
{
  Json::Value root {};
  root[ "networkThreadDelay" ] = networkThreadDelay_;
  root[ "frameLimit" ]         = frameLimit_;

  return root;
}

int ClientConfiguration::frameLimit()
{
  return frameLimit_;
}

int ClientConfiguration::networkThreadDelay()
{
  return networkThreadDelay_;
}

// Set defaults in the constructor
ClientConfiguration::ClientConfiguration()
    : networkThreadDelay_( 50 )
    , frameLimit_( 10 )
{
}

} // namespace MenAmongGods