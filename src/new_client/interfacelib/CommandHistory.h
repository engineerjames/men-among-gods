#ifndef MEN_AMONG_GODS_COMMAND_HISTORY_H
#define MEN_AMONG_GODS_COMMAND_HISTORY_H

#include <string>
#include <vector>

namespace MenAmongGods
{
class CommandHistory
{
public:
  CommandHistory();

  std::string getPreviousCommand();
  std::string getNextCommand();
  void        addCommand( std::string command );

private:
  std::vector< std::string >           cmdHistory_;
  std::vector< std::string >::iterator cmdIter_;
};
} // namespace MenAmongGods

#endif