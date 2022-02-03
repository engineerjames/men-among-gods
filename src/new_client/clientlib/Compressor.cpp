#include "Compressor.h"

#include <iostream>

Compressor::Compressor()
    : zStream()
    , isInitialized( false )
{
  isInitialized = inflateInit( &zStream );
}

int Compressor::inflate()
{
  return ::inflate( &zStream, Z_SYNC_FLUSH );
}

int Compressor::deflate()
{
  return ::deflate( &zStream, Z_SYNC_FLUSH );
}

// next input byte
void Compressor::setNextInput( void *input )
{
  zStream.next_in = static_cast< unsigned char * >( input );
}

// next output byte will go here
void Compressor::setNextOutput( void *output )
{
  zStream.next_out = static_cast< unsigned char * >( output );
}

// number of bytes available at next_in
void Compressor::setAvailableIn( std::uint32_t bytesAvailable )
{
  zStream.avail_in = bytesAvailable;
}

// number of bytes available at next_out
void Compressor::setAvailableOut( std::uint32_t bytesAvailable )
{
  zStream.avail_out = bytesAvailable;
}

std::uint32_t Compressor::getAvailableIn() const
{
  return zStream.avail_in;
}

std::uint32_t Compressor::getAvailableOut() const
{
  return zStream.avail_out;
}