#include "ClientConfiguration.h"

#include "ResourceLocations.h"

#include <fstream>
#include <nlohmann/json.hpp>

namespace MenAmongGods
{
ClientConfiguration ClientConfiguration::instance()
{
  static ClientConfiguration instance_ {};

  return instance_;
}

nlohmann::json ClientConfiguration::toJson() const
{
  nlohmann::json root {};

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
  std::ifstream  inputJsonFile { MenAmongGods::getConfigPath() + "config.json" };
  nlohmann::json root = nlohmann::json::parse( inputJsonFile );

  LOG_DEBUG( "Found configuration here: " + MenAmongGods::getConfigPath() + "config.json" )

  loggingEnabled_ = root[ "loggingEnabled" ].get< bool >();
  hostIpAddress_  = root[ "hostIpAddress" ].get< std::string >();
  hostPort_       = root[ "hostPort" ].get< int >();
  enableHpBars_   = root[ "enableHpBars" ].get< bool >();

  LOG_DEBUG_OBJ( *this, "Client configuration parameters" );
}

} // namespace MenAmongGods