#ifndef MEN_AMONG_GODS_CHALLENGE_COMMAND_H
#define MEN_AMONG_GODS_CHALLENGE_COMMAND_H

#include "ClientCommand.h"

namespace MenAmongGods
{
class ChallengeCommand : public ClientCommand
{
public:
  ChallengeCommand( std::int32_t challengeHash, std::uint32_t version, std::uint32_t raceAndSex );
  virtual ~ChallengeCommand() = default;

  virtual bool send( sf::TcpSocket& socket ) const override;

private:
  std::int32_t  challengeHash_;
  std::uint32_t version_;
  std::uint32_t raceAndSex_;
};
} // namespace MenAmongGods

#endif