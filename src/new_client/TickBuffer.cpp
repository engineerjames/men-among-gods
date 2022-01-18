#include "TickBuffer.h"

#include <cstring>
#include <iostream>

TickBuffer::TickBuffer()
    : compressor_()
    , tickBuffer_()
    , tickSize_( 0 )
    , tickStart_( 0 )
    , ticksInQueue_( 0 )
{
}

std::uint8_t *TickBuffer::getBufferStart() noexcept
{
  return &tickBuffer_.at( tickSize_ );
}

std::size_t TickBuffer::getAvailableBytes() noexcept
{
  return TickBuffer::TSIZE - tickSize_;
}

bool TickBuffer::receive( const std::array< std::uint8_t, 1024 > *buffer, std::size_t bytesToReceive )
{
  std::memcpy( getBufferStart(), buffer, bytesToReceive );
  tickSize_ += bytesToReceive;

  if ( tickSize_ >= tickStart_ + 2 )
  {
    int tmp = *( unsigned short * ) ( tickBuffer_.data() + tickStart_ );
    tmp &= 0x7fff;
    if ( tmp < 2 )
    {
      return false;
    }

    tickStart_ += tmp;
    ticksInQueue_++;
  }

  return true;
}

void TickBuffer::processTicks()
{
  static const constexpr std::size_t BUFFER_SIZE = 65536;

  unsigned short len   = 0;
  int            idx   = 0;
  int            csize = 0;
  int            comp  = 0;

  static unsigned char buf[ BUFFER_SIZE ];
  static int           ctot = 1;
  static int           utot = 1;
  static int           t    = 0;
  static int           td   = 0;

  if ( ! t )
  {
    t = time( NULL );
  }
  len  = *( unsigned short * ) ( tickBuffer_.data() );
  comp = len & 0x8000;
  len &= 0x7fff;
  ctot += len;
  if ( len > tickSize_ )
  {
    // return 0;
  }

  if ( comp )
  {
    compressor_.setNextInput( tickBuffer_.data() + 2 );
    compressor_.setAvailableIn( len - 2 );

    compressor_.setNextOutput( buf );
    compressor_.setAvailableOut( BUFFER_SIZE );

    int ret = compressor_.inflate();

    if ( ret != Z_OK )
    {
      std::cerr << "uncompress error!" << std::endl;
      std::cerr << "Error code is: " << ret << std::endl;
    }

    if ( compressor_.getAvailableIn() != 0 )
    {
      std::cerr << "uncompress: avail is " << compressor_.getAvailableIn() << std::endl;
    }

    csize = BUFFER_SIZE - compressor_.getAvailableOut();
  }
  else
  {
    csize = len - 2;
    if ( csize )
    {
      std::memcpy( buf, tickBuffer_.data() + 2, csize );
    }
  }

  utot += csize;

  td = time( NULL ) - t;
  if ( ! td )
  {
    td = 1;
  }

  // lastn = -1; // reset sv_setmap
  // ctick++;
  // if ( ctick > 19 )
  // {
  //   ctick = 0;
  // }

  while ( idx < csize )
  {
    int retVal = -1; // sv_cmd( buf + idx );
    if ( retVal == -1 )
    {
      std::cerr << "Warning: syntax error in server data";
      exit( 1 );
    }
    idx += retVal;
  }

  tickSize_ -= len;
  tickStart_ -= len;
  ticksInQueue_--;

  if ( tickSize_ != 0 )
  {
    std::memmove( tickBuffer_.data(), tickBuffer_.data() + len, tickSize_ );
  }

  // engine_tick();

  // return 1;
}