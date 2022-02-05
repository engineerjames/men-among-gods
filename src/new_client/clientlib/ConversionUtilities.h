#ifndef MEN_AMONG_GODS_CONVERSION_UTILITIES_H
#define MEN_AMONG_GODS_CONVERSION_UTILITIES_H

#include <array>
#include <iostream>
#include <sstream>
#include <string>

namespace MenAmongGods
{
template < std::size_t N > std::string convertArrayToStdString( const std::array< char, N >& inputArray )
{
  // TODO: Unsure if responses from the server are null-terminated which could cause
  // some horrendous bugs.  Let's be defensive and check for that here and throw some red
  // flags if we find otherwise.
  std::stringstream ss {};
  for ( const auto& c : inputArray )
  {
    ss << c;
  }

  if ( inputArray[ N - 1 ] != '\0' )
  {
    std::cerr << "Input array is NOT null terminated! ABORT ABORT ABORT!" << std::endl;
  }

  return ss.str();
}
} // namespace MenAmongGods

#endif