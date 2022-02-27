#include "ClientConfiguration.h"

#include "ConstantIdentifiers.h"
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

std::string ClientConfiguration::hostIpAddress() const
{
  return hostIpAddress_;
}

int ClientConfiguration::hostPort() const
{
  return hostPort_;
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
    , hostIpAddress_( "127.0.0.1" )
    , hostPort_( 5555 )
{
  // Read in the JSON parameters from the file
  std::ifstream inputJsonFile { MenAmongGods::getConfigPath() + "config.json" };
  Json::Value   root {};

  inputJsonFile >> root;

  networkThreadDelay_ = root.get( "networkThreadDelay", networkThreadDelay_ ).asInt();
  frameLimit_         = root.get( "frameLimit", frameLimit_ ).asInt();
  loggingEnabled_     = root.get( "loggingEnabled", loggingEnabled_ ).asBool();
  hostIpAddress_      = root.get( "hostIpAddress", hostIpAddress_ ).asString();
  hostPort_           = root.get( "hostPort", hostPort_ ).asInt();

  LOG_DEBUG_OBJ( *this, "Client configuration parameters" );
}

} // namespace MenAmongGods