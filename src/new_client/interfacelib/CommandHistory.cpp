#include "CommandHistory.h"

namespace MenAmongGods
{
CommandHistory::CommandHistory()
    : cmdHistory_()
    , cmdIter_()
{
}

// Down arrow
std::string CommandHistory::getNextCommand()
{
  if ( cmdHistory_.empty() )
  {
    return "";
  }

  if ( cmdIter_ == cmdHistory_.end() - 1)
  {
    return "";
  }
  else
  {
    cmdIter_++;

    return *cmdIter_;
  }
}

// Up arrow
std::string CommandHistory::getPreviousCommand()
{
  if ( cmdHistory_.empty() )
  {
    return "";
  }

  if ( cmdIter_ != cmdHistory_.begin() )
  {
    cmdIter_--;
    return *cmdIter_;
  }
  else
  {
    return *cmdHistory_.begin();
  }
}

void CommandHistory::addCommand( std::string command )
{
  cmdHistory_.push_back( command );
  cmdIter_ = cmdHistory_.end();
}

} // namespace MenAmongGods