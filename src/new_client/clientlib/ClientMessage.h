#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H

#include <cstdint>
#include <string>

namespace ClientMessages
{
enum struct MessageTypes : std::uint8_t
{
  EMPTY         = 0,
  NEWLOGIN      = 1,
  LOGIN         = 2,
  CHALLENGE     = 3,
  PERF_REPORT   = 4,
  CMD_MOVE      = 5,
  CMD_PICKUP    = 6,
  CMD_ATTACK    = 7,
  CMD_MODE      = 8,
  CMD_INV       = 9,
  CMD_STAT      = 10,
  CMD_DROP      = 11,
  CMD_GIVE      = 12,
  CMD_LOOK      = 13,
  CMD_INPUT1    = 14,
  CMD_INPUT2    = 15,
  CMD_INV_LOOK  = 16,
  CMD_LOOK_ITEM = 17,
  CMD_USE       = 18,
  CMD_SETUSER   = 19,
  CMD_TURN      = 20,
  CMD_AUTOLOOK  = 21,
  CMD_INPUT3    = 22,
  CMD_INPUT4    = 23,
  CMD_RESET     = 24,
  CMD_SHOP      = 25,
  CMD_SKILL     = 26,
  CMD_INPUT5    = 27,
  CMD_INPUT6    = 28,
  CMD_INPUT7    = 29,
  CMD_INPUT8    = 30,
  CMD_EXIT      = 31,
  CMD_UNIQUE    = 32,
  PASSWD        = 33,
  CMD_CTICK     = 255
};
std::uint8_t getValue( MessageTypes type );
MessageTypes getType( std::uint8_t value );
std::string  getName( MessageTypes type );

} // namespace ClientMessages

#endif // CLIENT_MESSAGE_H