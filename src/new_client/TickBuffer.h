#ifndef TICK_BUFFER_H
#define TICK_BUFFER_H

#include <array>
#include <cstdint>

#include "Compressor.h"

class TickBuffer
{
public:
  static constexpr const unsigned int TSIZE = 131072;

  TickBuffer();
  ~TickBuffer() = default;

  std::uint8_t *getBufferStart() noexcept;
  std::size_t   getAvailableBytes() noexcept;
  bool          receive( const std::array< std::uint8_t, 1024 > *buffer, std::size_t bytesToReceive );
  void          processTicks();

private:
  Compressor                        compressor_;
  std::array< std::uint8_t, TSIZE > tickBuffer_;
  unsigned int                      tickSize_;
  unsigned int                      tickStart_;
  unsigned int                      ticksInQueue_;
};

#endif