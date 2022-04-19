#ifndef MEN_AMONG_GODS_RANK_NAMES_H
#define MEN_AMONG_GODS_RANK_NAMES_H

#include <array>

namespace MenAmongGods
{
static const constexpr int                              NUMBER_OF_RANKS = 24;
extern const std::array< const char*, NUMBER_OF_RANKS > rankToString;
extern const std::array< const char*, NUMBER_OF_RANKS > rankToStringShort;


int points2rank( int v );

} // namespace MenAmongGods

#endif