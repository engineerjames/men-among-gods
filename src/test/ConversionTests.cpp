#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "ConversionUtilities.h"

#include <array>
#include <string>

BOOST_AUTO_TEST_SUITE( CONVERSION_UTILITIES_TESTS )

BOOST_AUTO_TEST_CASE( ARRAY_TO_STD_STRING )
{
  const char*            testValue = "This is a test!";
  std::array< char, 16 > inputArray {};

  std::strcpy( inputArray.data(), testValue );

  std::string expectedValue = "This is a test!";
  std::string actualValue   = MenAmongGods::convertArrayToStdString( inputArray );

  for ( unsigned int i = 0; i < 16; ++i )
  {
    BOOST_CHECK_EQUAL( expectedValue[ i ], actualValue[ i ] );
  }
}

BOOST_AUTO_TEST_CASE( EMPTY_STRING )
{
  const char*           testValue = "";
  std::array< char, 1 > inputArray {};

  std::strcpy( inputArray.data(), testValue );

  std::string expectedValue = "";
  std::string actualValue   = MenAmongGods::convertArrayToStdString( inputArray );

  for ( unsigned int i = 0; i < 1; ++i )
  {
    BOOST_CHECK_EQUAL( expectedValue[ i ], actualValue[ i ] );
  }
}

BOOST_AUTO_TEST_SUITE_END()