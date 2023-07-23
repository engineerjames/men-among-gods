#include "Catch.hpp"

#include "GuiFormatters.h"

#include <string>

TEST_CASE( ZERO_GOLD )
{
  std::string expectedValue = "0g 00s";
  std::string actualValue   = MenAmongGods::goldToString( 0 );

  REQUIRE( expectedValue == actualValue );
}

TEST_CASE( GOLD_ONLY )
{
  std::string expectedValue = "2g 00s";
  std::string actualValue   = MenAmongGods::goldToString( 200 );

  REQUIRE( expectedValue == actualValue );
}

TEST_CASE( SILVER_ONLY )
{
  std::string expectedValue = "0g 90s";
  std::string actualValue   = MenAmongGods::goldToString( 90 );

  REQUIRE( expectedValue == actualValue );
}

TEST_CASE( BOUNDARY_SILVER )
{
  std::string expectedValue = "0g 99s";
  std::string actualValue   = MenAmongGods::goldToString( 99 );

  REQUIRE( expectedValue == actualValue );
}

TEST_CASE( GOLD_AND_SILVER )
{
  std::string expectedValue = "1g 99s";
  std::string actualValue   = MenAmongGods::goldToString( 199 );

  REQUIRE( expectedValue == actualValue );
}


TEST_CASE( LESS_THAN_1000 )
{
  std::string expectedValue = "0";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( 0 );

  REQUIRE( expectedValue == actualValue );

  expectedValue = "999";
  actualValue   = MenAmongGods::addThousandsSeparator( 999 );

  REQUIRE( expectedValue == actualValue );
}

TEST_CASE( EXACTLY_1000 )
{
  std::string expectedValue = "1,000";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( 1000 );

  REQUIRE( expectedValue == actualValue );
}

TEST_CASE( OVER_9000 )
{
  std::string expectedValue = "9,998";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( 9998 );

  REQUIRE( expectedValue == actualValue );
}

TEST_CASE( OVER_10_000 )
{
  std::string expectedValue = "15,432";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( 15432 );

  REQUIRE( expectedValue == actualValue );
}

TEST_CASE( OVER_100_000 )
{
  std::string expectedValue = "186,326";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( 186326 );
  REQUIRE( expectedValue == actualValue );

  expectedValue = "542,121";
  actualValue   = MenAmongGods::addThousandsSeparator( 542121 );
  REQUIRE( expectedValue == actualValue );

  expectedValue = "986,326";
  actualValue   = MenAmongGods::addThousandsSeparator( 986326 );
  REQUIRE( expectedValue == actualValue );
}

TEST_CASE( NEGATIVE_NUMBERS )
{
  std::string expectedValue = "-186,326";
  std::string actualValue   = MenAmongGods::addThousandsSeparator( -186326 );
  REQUIRE( expectedValue == actualValue );

  expectedValue = "-999";
  actualValue   = MenAmongGods::addThousandsSeparator( -999 );
  REQUIRE( expectedValue == actualValue );

  expectedValue = "-100";
  actualValue   = MenAmongGods::addThousandsSeparator( -100 );
  REQUIRE( expectedValue == actualValue );
}