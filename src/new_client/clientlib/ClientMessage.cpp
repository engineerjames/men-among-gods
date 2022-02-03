#include "ClientMessage.h"

#include <map>

namespace ClientMessages // TODO: Fix Plural
{

namespace detail
{
const std::map< MessageTypes, std::string > typeToString = { { MessageTypes::EMPTY, "EMPTY" },
                                                             { MessageTypes::NEWLOGIN, "NEWLOGIN" },
                                                             { MessageTypes::LOGIN, "LOGIN" },
                                                             { MessageTypes::CHALLENGE, "CHALLENGE" },
                                                             { MessageTypes::PERF_REPORT, "PERF_REPORT" },
                                                             { MessageTypes::CMD_MOVE, "CMD_MOVE" },
                                                             { MessageTypes::CMD_PICKUP, "CMD_PICKUP" },
                                                             { MessageTypes::CMD_ATTACK, "CMD_ATTACK" },
                                                             { MessageTypes::CMD_MODE, "CMD_MODE" },
                                                             { MessageTypes::CMD_INV, "CMD_INV" },
                                                             { MessageTypes::CMD_STAT, "CMD_STAT" },
                                                             { MessageTypes::CMD_DROP, "CMD_DROP" },
                                                             { MessageTypes::CMD_GIVE, "CMD_GIVE" },
                                                             { MessageTypes::CMD_LOOK, "CMD_LOOK" },
                                                             { MessageTypes::CMD_INPUT1, "CMD_INPUT1" },
                                                             { MessageTypes::CMD_INPUT2, "CMD_INPUT2" },
                                                             { MessageTypes::CMD_INV_LOOK, "CMD_INV_LOOK" },
                                                             { MessageTypes::CMD_LOOK_ITEM, "CMD_LOOK_ITEM" },
                                                             { MessageTypes::CMD_USE, "CMD_USE" },
                                                             { MessageTypes::CMD_SETUSER, "CMD_SETUSER" },
                                                             { MessageTypes::CMD_TURN, "CMD_TURN" },
                                                             { MessageTypes::CMD_AUTOLOOK, "CMD_AUTOLOOK" },
                                                             { MessageTypes::CMD_INPUT3, "CMD_INPUT3" },
                                                             { MessageTypes::CMD_INPUT4, "CMD_INPUT4" },
                                                             { MessageTypes::CMD_RESET, "CMD_RESET" },
                                                             { MessageTypes::CMD_SHOP, "CMD_SHOP" },
                                                             { MessageTypes::CMD_SKILL, "CMD_SKILL" },
                                                             { MessageTypes::CMD_INPUT5, "CMD_INPUT5" },
                                                             { MessageTypes::CMD_INPUT6, "CMD_INPUT6" },
                                                             { MessageTypes::CMD_INPUT7, "CMD_INPUT7" },
                                                             { MessageTypes::CMD_INPUT8, "CMD_INPUT8" },
                                                             { MessageTypes::CMD_EXIT, "CMD_EXIT" },
                                                             { MessageTypes::CMD_UNIQUE, "CMD_UNIQUE" },
                                                             { MessageTypes::PASSWD, "PASSWD" },
                                                             { MessageTypes::CMD_CTICK, "CMD_CTICK" } };
}

std::uint8_t getValue( MessageTypes type ) { return static_cast< uint8_t >( type ); }

MessageTypes getType( std::uint8_t value ) { return static_cast< MessageTypes >( value ); }

std::string getName( MessageTypes type ) { return detail::typeToString.at( type ); }

} // namespace ClientMessages