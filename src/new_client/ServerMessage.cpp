#include "ServerMessage.h"

#include <map>

namespace ServerMessages
{

namespace detail
{
const std::map< MessageTypes, std::string > typeToString = { { MessageTypes::EMPTY, "EMPTY" },
                                                             { MessageTypes::CHALLENGE, "CHALLENGE" },
                                                             { MessageTypes::NEWPLAYER, "NEWPLAYER" },
                                                             { MessageTypes::SETCHAR_NAME1, "SETCHAR_NAME1" },
                                                             { MessageTypes::SETCHAR_NAME2, "SETCHAR_NAME2" },
                                                             { MessageTypes::SETCHAR_NAME3, "SETCHAR_NAME3" },
                                                             { MessageTypes::SETCHAR_MODE, "SETCHAR_MODE" },
                                                             { MessageTypes::SETCHAR_ATTRIB, "SETCHAR_ATTRIB" },
                                                             { MessageTypes::SETCHAR_SKILL, "SETCHAR_SKILL" },
                                                             { MessageTypes::SETCHAR_HP, "SETCHAR_HP" },
                                                             { MessageTypes::SETCHAR_ENDUR, "SETCHAR_ENDUR" },
                                                             { MessageTypes::SETCHAR_MANA, "SETCHAR_MANA" },
                                                             { MessageTypes::SETCHAR_AHP, "SETCHAR_AHP" },
                                                             { MessageTypes::SETCHAR_PTS, "SETCHAR_PTS" },
                                                             { MessageTypes::SETCHAR_GOLD, "SETCHAR_GOLD" },
                                                             { MessageTypes::SETCHAR_ITEM, "SETCHAR_ITEM" },
                                                             { MessageTypes::SETCHAR_WORN, "SETCHAR_WORN" },
                                                             { MessageTypes::SETCHAR_OBJ, "SETCHAR_OBJ" },
                                                             { MessageTypes::TICK, "TICK" },
                                                             { MessageTypes::LOOK1, "LOOK1" },
                                                             { MessageTypes::SCROLL_RIGHT, "SCROLL_RIGHT" },
                                                             { MessageTypes::SCROLL_LEFT, "SCROLL_LEFT" },
                                                             { MessageTypes::SCROLL_UP, "SCROLL_UP" },
                                                             { MessageTypes::SCROLL_DOWN, "SCROLL_DOWN" },
                                                             { MessageTypes::LOGIN_OK, "LOGIN_OK" },
                                                             { MessageTypes::SCROLL_RIGHTUP, "SCROLL_RIGHTUP" },
                                                             { MessageTypes::SCROLL_RIGHTDOWN, "SCROLL_RIGHTDOWN" },
                                                             { MessageTypes::SCROLL_LEFTUP, "SCROLL_LEFTUP" },
                                                             { MessageTypes::SCROLL_LEFTDOWN, "SCROLL_LEFTDOWN" },
                                                             { MessageTypes::LOOK2, "LOOK2" },
                                                             { MessageTypes::LOOK3, "LOOK3" },
                                                             { MessageTypes::LOOK4, "LOOK4" },
                                                             { MessageTypes::SETTARGET, "SETTARGET" },
                                                             { MessageTypes::SETMAP2, "SETMAP2" },
                                                             { MessageTypes::SETORIGIN, "SETORIGIN" },
                                                             { MessageTypes::SETMAP3, "SETMAP3" },
                                                             { MessageTypes::SETCHAR_SPELL, "SETCHAR_SPELL" },
                                                             { MessageTypes::PLAYSOUND, "PLAYSOUND" },
                                                             { MessageTypes::EXIT, "EXIT" },
                                                             { MessageTypes::MSG, "MSG" },
                                                             { MessageTypes::LOOK5, "LOOK5" },
                                                             { MessageTypes::LOOK6, "LOOK6" },
                                                             { MessageTypes::LOG, "LOG" },
                                                             { MessageTypes::LOG0, "LOG0" },
                                                             { MessageTypes::LOG1, "LOG1" },
                                                             { MessageTypes::LOG2, "LOG2" },
                                                             { MessageTypes::LOG3, "LOG3" },
                                                             { MessageTypes::LOAD, "LOAD" },
                                                             { MessageTypes::CAP, "CAP" },
                                                             { MessageTypes::MOD1, "MOD1" },
                                                             { MessageTypes::MOD2, "MOD2" },
                                                             { MessageTypes::MOD3, "MOD3" },
                                                             { MessageTypes::MOD4, "MOD4" },
                                                             { MessageTypes::MOD5, "MOD5" },
                                                             { MessageTypes::MOD6, "MOD6" },
                                                             { MessageTypes::MOD7, "MOD7" },
                                                             { MessageTypes::MOD8, "MOD8" },
                                                             { MessageTypes::SETMAP4, "SETMAP4" },
                                                             { MessageTypes::SETMAP5, "SETMAP5" },
                                                             { MessageTypes::SETMAP6, "SETMAP6" },
                                                             { MessageTypes::SETCHAR_AEND, "SETCHAR_AEND" },
                                                             { MessageTypes::SETCHAR_AMANA, "SETCHAR_AMANA" },
                                                             { MessageTypes::SETCHAR_DIR, "SETCHAR_DIR" },
                                                             { MessageTypes::UNIQUE, "UNIQUE" },
                                                             { MessageTypes::IGNORE, "IGNORE" },
                                                             { MessageTypes::SETMAP, "SETMAP" } };
}

std::uint8_t getValue( MessageTypes type ) { return static_cast< uint8_t >( type ); }

MessageTypes getType( std::uint8_t value ) { return static_cast< MessageTypes >( value ); }

std::string getName( MessageTypes type ) { return detail::typeToString.at( type ); }

} // namespace ServerMessages