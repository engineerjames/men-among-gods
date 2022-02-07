#ifndef MEN_AMONG_GODS_SAY_COMMAND_H
#define MEN_AMONG_GODS_SAY_COMMAND_H

#include "ClientCommand.h"

#include <array>

namespace MenAmongGods
{
class SayCommand : public ClientCommand< CommandType, CommandType::CL_EMPTY >
{
public:
  SayCommand( const std::string& statement );
  virtual ~SayCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  bool sendPartialMessage( sf::TcpSocket& socket, const std::array< char, 250 >& stringBuffer, CommandType inputType ) const;

  std::string statement_;
};
} // namespace MenAmongGods

#endif