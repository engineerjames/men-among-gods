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

  root[ "loggingEnabled" ] = loggingEnabled_;
  root[ "enableHpBars" ]   = enableHpBars_;
  root[ "hostPort" ]       = hostPort_;
  root[ "hostIpAddress" ]  = hostIpAddress_;

  return root;
}

bool ClientConfiguration::enableHpBars() const
{
  return enableHpBars_;
}

std::string ClientConfiguration::hostIpAddress() const
{
  return hostIpAddress_;
}

int ClientConfiguration::hostPort() const
{
  return hostPort_;
}

bool ClientConfiguration::loggingEnabled() const
{
  return loggingEnabled_;
}

// Set defaults in the constructor
ClientConfiguration::ClientConfiguration()
    : loggingEnabled_( false )
    , hostIpAddress_( "127.0.0.1" )
    , hostPort_( 5555 )
    , enableHpBars_( false )
{
  // Read in the JSON parameters from the file
  std::ifstream inputJsonFile { MenAmongGods::getConfigPath() + "config.json" };
  Json::Value   root {};

  inputJsonFile >> root;

  loggingEnabled_ = root.get( "loggingEnabled", loggingEnabled_ ).asBool();
  hostIpAddress_  = root.get( "hostIpAddress", hostIpAddress_ ).asString();
  hostPort_       = root.get( "hostPort", hostPort_ ).asInt();
  enableHpBars_   = root.get( "enableHpBars", enableHpBars_ ).asBool();

  LOG_DEBUG_OBJ( *this, "Client configuration parameters" );
}

} // namespace MenAmongGods