#ifndef ENCODER_H
#define ENCODER_H

#include <cstdint>

class Encoder
{
public:
  static std::uint32_t xcrypt( std::uint32_t val );
};

#endif