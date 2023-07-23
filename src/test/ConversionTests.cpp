#include "Catch.hpp"

#include "ConversionUtilities.h"

#include <array>
#include <string>

TEST_CASE( ARRAY_TO_STD_STRING )
{
  const char*            testValue = "This is a test!";
  std::array< char, 16 > inputArray {};

  std::strcpy( inputArray.data(), testValue );

  std::string expectedValue = "This is a test!";
  std::string actualValue   = MenAmongGods::convertArrayToStdString( inputArray );

  for ( unsigned int i = 0; i < 16; ++i )
  {
    REQUIRE( expectedValue[ i ] == actualValue[ i ] );
  }
}

TEST_CASE( EMPTY_STRING )
{
  const char*           testValue = "";
  std::array< char, 1 > inputArray {};

  std::strcpy( inputArray.data(), testValue );

  std::string expectedValue = "";
  std::string actualValue   = MenAmongGods::convertArrayToStdString( inputArray );

  for ( unsigned int i = 0; i < 1; ++i )
  {
    REQUIRE( expectedValue[ i ] == actualValue[ i ] );
  }
}