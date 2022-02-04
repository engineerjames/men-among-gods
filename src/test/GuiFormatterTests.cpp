#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "GuiFormatters.h"

#include <string>

BOOST_AUTO_TEST_SUITE( GOLD_TO_STRING_TESTS )

BOOST_AUTO_TEST_CASE( ZERO_GOLD )
{
  std::string expectedValue = "0g 00s";
  std::string actualValue   = MenAmongGods::goldToString( 0 );

  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_CASE( GOLD_ONLY )
{
  std::string expectedValue = "2g 00s";
  std::string actualValue   = MenAmongGods::goldToString( 200 );

  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_CASE( SILVER_ONLY )
{
  std::string expectedValue = "0g 90s";
  std::string actualValue   = MenAmongGods::goldToString( 90 );

  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_CASE( BOUNDARY_SILVER )
{
  std::string expectedValue = "0g 99s";
  std::string actualValue   = MenAmongGods::goldToString( 99 );

  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_CASE( GOLD_AND_SILVER )
{
  std::string expectedValue = "1g 99s";
  std::string actualValue   = MenAmongGods::goldToString( 199 );

  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_SUITE_END()