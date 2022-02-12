#include "Logger.h"

#include <iostream>

namespace MenAmongGods::detail
{
Logger& Logger::instance()
{
  static Logger logger { "./playerLog.json" };
  return logger;
}

Logger::Logger( std::string fileName )
    : jsonLogEntries_()
    , outputFile_( fileName, std::ios::app )
    , logMutex_()
    , currentLogLevel_( Logger::Level::DEBUG )
{
}

void Logger::setLogLevel( Logger::Level newLevel )
{
  currentLogLevel_ = newLevel;
}

Logger::~Logger()
{
  Json::Value root = Json::arrayValue;

  {
    std::lock_guard< std::mutex > lock( logMutex_ );
    for ( const auto& e : jsonLogEntries_ )
    {
      e.toJson( root );
    }
  }

  // TODO: Write things out as we receive them
  if ( outputFile_.is_open() )
  {
    outputFile_ << root.toStyledString();
  }
  else
  {
    std::cerr << "Unable to write log file!" << std::endl;
  }
}

} // namespace MenAmongGods::detail