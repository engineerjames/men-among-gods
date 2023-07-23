#define CATCH_CONFIG_MAIN
#include "Catch.hpp"

#include "CommandHistory.h"

#include <array>
#include <string>

TEST_CASE( "GET_PREVIOUS_COMMAND" )
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

  REQUIRE( firstCommand == "c" );
  REQUIRE( secondCommand == "b" );
  REQUIRE( thirdCommand == "a" );
  REQUIRE( fourthCommand == "a" );
  REQUIRE( fifthCommand == "a" );
}

TEST_CASE( "EMPTY_COMMAND_HISTORY" )
{
  MenAmongGods::CommandHistory history {};

  std::string previousCommand = history.getPreviousCommand();
  std::string nextCommand     = history.getNextCommand();

  REQUIRE( previousCommand == "" );
  REQUIRE( nextCommand == "" );
}

TEST_CASE( "BACK_AND_FORTH" )
{
  MenAmongGods::CommandHistory history {};

  history.addCommand( "a" );
  history.addCommand( "b" );
  history.addCommand( "c" );

  std::string firstCommand  = history.getPreviousCommand();
  std::string secondCommand = history.getPreviousCommand();
  std::string thirdCommand  = history.getNextCommand();
  std::string fourthCommand = history.getPreviousCommand();
  std::string fifthCommand  = history.getNextCommand();
  std::string sixthCommand  = history.getNextCommand();

  REQUIRE( firstCommand == "c" );
  REQUIRE( secondCommand == "b" );
  REQUIRE( thirdCommand == "c" );
  REQUIRE( fourthCommand == "b" );
  REQUIRE( fifthCommand == "c" );
  REQUIRE( sixthCommand == "" );
}