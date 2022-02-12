#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// Hackery to allow for white-box testing of class internals
#define private public
#include "Logger.h"
#undef private

#include <array>
#include <iostream>
#include <json/json.h>
#include <string>

BOOST_AUTO_TEST_SUITE( LOGGING_TESTS )

BOOST_AUTO_TEST_CASE( DEBUG_LOG_WORKS )
{
  LOG_DEBUG( "Hello world" );

  std::size_t actualCount   = MenAmongGods::detail::Logger::instance().jsonLogEntries_.size();
  std::size_t expectedCount = 1;

  BOOST_CHECK_EQUAL( expectedCount, actualCount );

  auto expectedLogLevel = MenAmongGods::detail::Logger::Level::DEBUG;
  auto actualLogLevel   = MenAmongGods::detail::Logger::instance().jsonLogEntries_[ 0 ].level_;

  BOOST_ASSERT( expectedLogLevel == actualLogLevel );
}

BOOST_AUTO_TEST_CASE( CAN_JSONIFY_LOG_ENTRY )
{
  MenAmongGods::detail::Logger::LogEntry entry { Json::nullValue, "This is the message", MenAmongGods::detail::Logger::Level::DEBUG,
                                                 "testfile.cpp", 53, "testFunction" };
  Json::Value                            json {};
  entry.toJson( json );

  std::cerr << "Time Value: " << json[ 0 ][ "time" ].asString() << std::endl;

  BOOST_CHECK_EQUAL( "This is the message", json[ 0 ][ "msg" ].asString() );
  BOOST_CHECK_EQUAL( "DEBUG", json[ 0 ][ "level" ].asString() );
  BOOST_CHECK_EQUAL( 53, json[ 0 ][ "lineNumber" ].asInt() );
  BOOST_CHECK_EQUAL( "testfile.cpp", json[ 0 ][ "file" ].asString() );
  BOOST_CHECK_EQUAL( "testFunction", json[ 0 ][ "function" ].asString() );
}

BOOST_AUTO_TEST_SUITE_END()