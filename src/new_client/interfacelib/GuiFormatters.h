#ifndef GUI_FORMATTERS_H
#define GUI_FORMATTERS_H

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace MenAmongGods
{

template < typename T > std::string goldToString( T goldValue )
{
  if ( goldValue == 0 )
  {
    return "0g 0s";
  }

  std::stringstream ss {};

  // 20 is 20s
  // 200 is 2g 00s
  // 1200 is 12 gold 00s
  int         goldAmount   = goldValue / 100;
  std::string silverAmount = std::to_string( goldValue );

  // TODO: Fix check when silver = "0"
  std::string finalSilverAmount = silverAmount.substr( silverAmount.length() - 2, 2 );

  ss << goldAmount << "g " << finalSilverAmount << "s";

  return ss.str();
}

template < typename T > std::string addThousandsSeparator( T value )
{
  if constexpr ( std::is_integral_v< T > )
  {
    if ( value < 1000 )
    {
      return std::to_string( value );
    }
    else // more than 1,000
    {
      std::string newString = std::to_string( value );
      for ( unsigned int i = newString.length() - 1; i > 0; --i )
      {
        if ( i % 3 == 0 )
        {
          newString.insert( newString.length() - i, 1, ',' );
        }
      }

      return newString;
    }
  }
  else
  {
    return "UNSUPPORTED DATA TYPE"; // You are attempting to use this function with the wrong type--should be a int of some variety.
  }
}
} // namespace MenAmongGods
#endif