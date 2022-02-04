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

BOOST_AUTO_TEST_SUITE( THOUSANDS_SEPARATOR_TESTS )

BOOST_AUTO_TEST_CASE( LESS_THAN_1000 )
{
  std::string expectedValue = "0";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( 0 );

  BOOST_CHECK_EQUAL( expectedValue, actualValue );

  expectedValue = "999";
  actualValue   = MenAmongGods::addThousandsSeparator( 999 );

  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_CASE( EXACTLY_1000 )
{
  std::string expectedValue = "1,000";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( 1000 );

  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_CASE( OVER_9000 )
{
  std::string expectedValue = "9,998";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( 9998 );

  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_CASE( OVER_10_000 )
{
  std::string expectedValue = "15,432";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( 15432 );

  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_CASE( OVER_100_000 )
{
  std::string expectedValue = "186,326";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( 186326 );
  BOOST_CHECK_EQUAL( expectedValue, actualValue );

  expectedValue = "542,121";
  actualValue   = MenAmongGods::addThousandsSeparator( 542121 );
  BOOST_CHECK_EQUAL( expectedValue, actualValue );

  expectedValue = "986,326";
  actualValue   = MenAmongGods::addThousandsSeparator( 986326 );
  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_CASE( NEGATIVE_NUMBERS )
{
  std::string expectedValue = "-186,326";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( -186326 );
  BOOST_CHECK_EQUAL( expectedValue, actualValue );

  expectedValue = "-999";
  actualValue   = MenAmongGods::addThousandsSeparator( -999 );
  BOOST_CHECK_EQUAL( expectedValue, actualValue );

  expectedValue = "-100";
  actualValue   = MenAmongGods::addThousandsSeparator( -100 );
  BOOST_CHECK_EQUAL( expectedValue, actualValue );
}

BOOST_AUTO_TEST_SUITE_END()