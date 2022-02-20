#include "ClientConfiguration.h"

#include "ResourceLocations.h"

#include <fstream>
#include <json/json.h>

namespace MenAmongGods
{
ClientConfiguration ClientConfiguration::instance()
{
  static ClientConfiguration instance_ {};

  return instance_;
}

Json::Value ClientConfiguration::toJson() const
{
  Json::Value root {};
  root[ "networkThreadDelay" ] = networkThreadDelay_;
  root[ "frameLimit" ]         = frameLimit_;
  root[ "loggingEnabled" ]     = loggingEnabled_;

  return root;
}

int ClientConfiguration::frameLimit() const
{
  return frameLimit_;
}

int ClientConfiguration::networkThreadDelay() const
{
  return networkThreadDelay_;
}

bool ClientConfiguration::loggingEnabled() const
{
  return loggingEnabled_;
}

// Set defaults in the constructor
ClientConfiguration::ClientConfiguration()
    : networkThreadDelay_( 50 )
    , frameLimit_( 10 )
    , loggingEnabled_( false )
{
  // Read in the JSON parameters from the file
  std::ifstream inputJsonFile { MenAmongGods::getConfigPath() + "config.json" };
  Json::Value   root {};

  inputJsonFile >> root;

  networkThreadDelay_ = root.get( "networkThreadDelay", networkThreadDelay_ ).asInt();
  frameLimit_         = root.get( "frameLimit", frameLimit_ ).asInt();
  loggingEnabled_     = root.get( "loggingEnabled", loggingEnabled_ ).asBool();

  LOG_DEBUG_OBJ( *this, "Client configuration parameters" );
}

} // namespace MenAmongGods