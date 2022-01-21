#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <cstdint>
#include <string>

namespace ServerMessages
{
enum struct MessageTypes : std::uint8_t
{
  EMPTY            = 0,
  CHALLENGE        = 1,
  NEWPLAYER        = 2,
  SETCHAR_NAME1    = 3,
  SETCHAR_NAME2    = 4,
  SETCHAR_NAME3    = 5,
  SETCHAR_MODE     = 6,
  SETCHAR_ATTRIB   = 7,
  SETCHAR_SKILL    = 8,
  SETCHAR_HP       = 12,
  SETCHAR_ENDUR    = 13,
  SETCHAR_MANA     = 14,
  SETCHAR_AHP      = 20,
  SETCHAR_PTS      = 21,
  SETCHAR_GOLD     = 22,
  SETCHAR_ITEM     = 23,
  SETCHAR_WORN     = 24,
  SETCHAR_OBJ      = 25,
  TICK             = 27,
  LOOK1            = 29,
  SCROLL_RIGHT     = 30,
  SCROLL_LEFT      = 31,
  SCROLL_UP        = 32,
  SCROLL_DOWN      = 33,
  LOGIN_OK         = 34,
  SCROLL_RIGHTUP   = 35,
  SCROLL_RIGHTDOWN = 36,
  SCROLL_LEFTUP    = 37,
  SCROLL_LEFTDOWN  = 38,
  LOOK2            = 39,
  LOOK3            = 40,
  LOOK4            = 41,
  SETTARGET        = 42,
  SETMAP2          = 43,
  SETORIGIN        = 44,
  SETMAP3          = 45,
  SETCHAR_SPELL    = 46,
  PLAYSOUND        = 47,
  EXIT             = 48,
  MSG              = 49,
  LOOK5            = 50,
  LOOK6            = 51,
  LOG              = 52,
  LOG0             = 52,
  LOG1             = 53,
  LOG2             = 54,
  LOG3             = 55,
  LOAD             = 56,
  CAP              = 57,
  MOD1             = 58,
  MOD2             = 59,
  MOD3             = 60,
  MOD4             = 61,
  MOD5             = 62,
  MOD6             = 63,
  MOD7             = 64,
  MOD8             = 65,
  SETMAP4          = 66,
  SETMAP5          = 67,
  SETMAP6          = 68,
  SETCHAR_AEND     = 69,
  SETCHAR_AMANA    = 70,
  SETCHAR_DIR      = 71,
  UNIQUE           = 72,
  IGNORE           = 73,
  SETMAP           = 128
};
std::uint8_t getValue( MessageTypes type );
MessageTypes getType( std::uint8_t value );
std::string  getName( MessageTypes type );

// Random notes: lots of 129's, then
// 42 SETTARGET
// 128 (SETMAP)
// 29 LOOK1
// 39 LOOK2
// 40 LOOK3
// 41 LOOK4
// 50 LOOK5

// 29
// 39
// 40
// 41
// 50

// 55

} // namespace ServerMessages

#endif // SERVER_MESSAGE_H