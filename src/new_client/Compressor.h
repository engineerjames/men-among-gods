#ifndef COMPRESSOR_H
#define COMPRESSOR_H // Modules can't come fast enough

#include <cstddef>
#include <cstdint>
#include <zlib.h>

class Compressor
{

public:
  Compressor();
  ~Compressor() = default;

  int inflate();

  // next input byte
  void setNextInput( void *input );

  // next output byte will go here
  void setNextOutput( void *output );

  // number of bytes available at next_in
  void setAvailableIn( std::uint32_t bytesAvailable );

  // number of bytes available at next_out
  void setAvailableOut( std::uint32_t bytesAvailable );

  std::uint32_t getAvailableIn() const;
  std::uint32_t getAvailableOut() const;

private:
  z_stream_s zStream;
  bool isInitialized;
};

#endif