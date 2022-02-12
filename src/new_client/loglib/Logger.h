#ifndef MEN_AMONG_GODS_LOGGING_H
#define MEN_AMONG_GODS_LOGGING_H

#include <chrono>
#include <codecvt>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <locale>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

#include <json/json.h>

namespace MenAmongGods::detail
{

inline std::string wtime( const time_t& t )
{
  using convert_typeX = std::codecvt_utf8< wchar_t >;

  std::tm            tm = *std::localtime( &t );
  std::wstringstream wss;
  wss << std::put_time( &tm, L"%F %T" );

  std::wstring_convert< convert_typeX, wchar_t > converterX;

  return converterX.to_bytes( wss.str() );
}

class Logger
{
public:
  static Logger& instance();

  enum struct Level
  {
    DEBUG,
    WARNING,
    ERROR
  };

  struct LogEntry
  {
    const Json::Value json_;
    const std::string msg_;
    const Level       level_;
    const std::string file_;
    const int         lineNumber_;
    const std::time_t currentTime_;
    std::string       functionName_;

    LogEntry( Json::Value json, std::string msg, Level level, std::string file, int lineNumber, std::string functionName )
        : json_( json )
        , msg_( msg )
        , level_( level )
        , file_( file )
        , lineNumber_( lineNumber )
        , currentTime_( std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() ) )
        , functionName_( functionName )
    {
    }

    void toJson( Json::Value& arrayRoot ) const
    {
      Json::Value root {};

      root[ "time" ] = wtime( currentTime_ );
      root[ "msg" ]  = msg_;

      if ( json_ != Json::nullValue )
      {
        root[ "object" ] = json_;
      }

      std::string levelString {};
      switch ( level_ )
      {
      case Level::DEBUG:
        levelString = "DEBUG";
        break;
      case Level::WARNING:
        levelString = "WARNING";
        break;
      case Level::ERROR:
        levelString = "ERROR";
        break;
      default:
        levelString = "UNKNOWN";
        break;
      }
      root[ "level" ]      = levelString;
      root[ "file" ]       = file_;
      root[ "lineNumber" ] = lineNumber_;
      root[ "function" ]   = functionName_;

      arrayRoot.append( root );
    }
  };

  void setLogLevel( Level newLevel );

  void addLogEntry( std::string msg, Level level, std::string file, int lineNumber, std::string function )
  {
    if ( level < currentLogLevel_ )
    {
      return;
    }

    LogEntry newEntry { Json::nullValue, msg, level, file, lineNumber, function };

    std::lock_guard< std::mutex > lock( logMutex_ );
    jsonLogEntries_.push_back( newEntry );
  }

  template < typename T >
  void addLogEntry( const T& jsonifiedObject, std::string msg, Level level, std::string file, int lineNumber, std::string function )
  {
    if ( level < currentLogLevel_ )
    {
      return;
    }

    LogEntry newEntry { jsonifiedObject.toJson(), msg, level, file, lineNumber, function };

    std::lock_guard< std::mutex > lock( logMutex_ );
    jsonLogEntries_.push_back( newEntry );
  }

private:
  Logger( std::string fileName );
  ~Logger();

  std::vector< LogEntry > jsonLogEntries_;
  std::fstream            outputFile_;
  std::mutex              logMutex_;
  Level                   currentLogLevel_;
};

} // namespace MenAmongGods::detail

#ifdef ENABLE_LOGGING

// TODO: Reduce duplication here.
#define LOG_DEBUG( msg )                                                                                                                   \
  {                                                                                                                                        \
    std::stringstream ss {};                                                                                                               \
    ss << msg;                                                                                                                             \
    MenAmongGods::detail::Logger::instance().addLogEntry( ss.str(), MenAmongGods::detail::Logger::Level::DEBUG, __FILE__, __LINE__,        \
                                                          __PRETTY_FUNCTION__ );                                                           \
  }

#define LOG_WARNING( msg )                                                                                                                 \
  {                                                                                                                                        \
    std::stringstream ss {};                                                                                                               \
    ss << msg;                                                                                                                             \
    MenAmongGods::detail::Logger::instance().addLogEntry( ss.str(), MenAmongGods::detail::Logger::Level::WARNING, __FILE__, __LINE__,      \
                                                          __PRETTY_FUNCTION__ );                                                           \
  }

#define LOG_ERROR( msg )                                                                                                                   \
  {                                                                                                                                        \
    std::stringstream ss {};                                                                                                               \
    ss << msg;                                                                                                                             \
    MenAmongGods::detail::Logger::instance().addLogEntry( ss.str(), MenAmongGods::detail::Logger::Level::ERROR, __FILE__, __LINE__,        \
                                                          __PRETTY_FUNCTION__ );                                                           \
  }

#define LOG_DEBUG_OBJ( obj, msg )                                                                                                          \
  {                                                                                                                                        \
    std::stringstream ss {};                                                                                                               \
    ss << msg;                                                                                                                             \
    MenAmongGods::detail::Logger::instance().addLogEntry( obj, ss.str(), MenAmongGods::detail::Logger::Level::DEBUG, __FILE__, __LINE__,   \
                                                          __PRETTY_FUNCTION__ );                                                           \
  }

#define LOG_WARNING_OBJ( obj, msg )                                                                                                        \
  {                                                                                                                                        \
    std::stringstream ss {};                                                                                                               \
    ss << msg;                                                                                                                             \
    MenAmongGods::detail::Logger::instance().addLogEntry( obj, ss.str(), MenAmongGods::detail::Logger::Level::WARNING, __FILE__, __LINE__, \
                                                          __PRETTY_FUNCTION__ );                                                           \
  }

#define LOG_ERROR_OBJ( obj, msg )                                                                                                          \
  {                                                                                                                                        \
    std::stringstream ss {};                                                                                                               \
    ss << msg;                                                                                                                             \
    MenAmongGods::detail::Logger::instance().addLogEntry( obj, ss.str(), MenAmongGods::detail::Logger::Level::ERROR, __FILE__, __LINE__,   \
                                                          __PRETTY_FUNCTION__ );                                                           \
  }

#else // No-ops

#define LOG_DEBUG( msg )
#define LOG_WARNING( msg )
#define LOG_ERROR( msg )
#define LOG_DEBUG_OBJ( msg )
#define LOG_WARNING_OBJ( msg )
#define LOG_ERROR_OBJ( msg )

#endif

#endif