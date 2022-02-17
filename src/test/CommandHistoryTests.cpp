#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "CommandHistory.h"

#include <array>
#include <string>

BOOST_AUTO_TEST_SUITE( COMMAND_HISTORY_TESTS )

BOOST_AUTO_TEST_CASE( GET_PREVIOUS_COMMAND )
{
  MenAmongGods::CommandHistory history {};
  history.addCommand( "a" );
  history.addCommand( "b" );
  history.addCommand( "c" );

  std::string firstCommand  = history.getPreviousCommand();
  std::string secondCommand = history.getPreviousCommand();
  std::string thirdCommand  = history.getPreviousCommand();
  std::string fourthCommand = history.getPreviousCommand();
  std::string fifthCommand  = history.getPreviousCommand();

  BOOST_CHECK_EQUAL( firstCommand, "c" );
  BOOST_CHECK_EQUAL( secondCommand, "b" );
  BOOST_CHECK_EQUAL( thirdCommand, "a" );
  BOOST_CHECK_EQUAL( fourthCommand, "a" );
  BOOST_CHECK_EQUAL( fifthCommand, "a" );
}

BOOST_AUTO_TEST_CASE( EMPTY_COMMAND_HISTORY )
{
  MenAmongGods::CommandHistory history {};

  std::string previousCommand = history.getPreviousCommand();
  std::string nextCommand     = history.getNextCommand();

  BOOST_CHECK_EQUAL( previousCommand, "" );
  BOOST_CHECK_EQUAL( nextCommand, "" );
}

BOOST_AUTO_TEST_SUITE_END()