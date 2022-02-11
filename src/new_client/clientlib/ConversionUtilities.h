#ifndef MEN_AMONG_GODS_CONVERSION_UTILITIES_H
#define MEN_AMONG_GODS_CONVERSION_UTILITIES_H

#include <array>
#include <iostream>
#include <sstream>
#include <string>

#include "Logger.h"

namespace MenAmongGods
{
template < std::size_t N > std::string convertArrayToStdString( const std::array< char, N >& inputArray )
{
  // TODO: Unsure if responses from the server are null-terminated which could cause
  // some horrendous bugs.  Let's be defensive and check for that here and throw some red
  // flags if we find otherwise.
  std::stringstream stringStream {};
  for ( const auto& c : inputArray )
  {
    stringStream << c;
  }

  if ( inputArray[ N - 1 ] != '\0' )
  {
    LOG_ERROR( "Input array is NOT null terminated!" );
  }

  return stringStream.str();
}
} // namespace MenAmongGods

#endif