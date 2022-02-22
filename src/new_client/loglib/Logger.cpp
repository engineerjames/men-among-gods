#include "Logger.h"

#include "ResourceLocations.h"

namespace MenAmongGods::detail
{
Logger& Logger::instance()
{
  static Logger logger { "./playerLog.json" };
  return logger;
}

Logger::Logger( std::string fileName )
    : outputFile_( fileName, std::ios::app )
    , logMutex_()
    , currentLogLevel_( Logger::Level::DEBUG )
{
  addLogEntry( GIT_REVISION, Level::DEBUG, "Logger.cpp", 21, "Constructor" );
}

void Logger::setLogLevel( Logger::Level newLevel )
{
  currentLogLevel_ = newLevel;
}

void Logger::addLogEntry( std::string msg, Level level, std::string file, int lineNumber, std::string function )
{
  if ( level < currentLogLevel_ )
  {
    return;
  }

  LogEntry newEntry { Json::nullValue, msg, level, file, lineNumber, function };

  std::lock_guard< std::mutex > lock( logMutex_ );
  writeEntryToFile( newEntry );
}
} // namespace MenAmongGods::detail