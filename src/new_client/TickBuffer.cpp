#include "TickBuffer.h"

#include <cstring>
#include <iostream>

#include "ServerMessage.h"

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

  int idx   = 0;
  int csize = 0;
  int comp  = 0;

  static std::uint8_t buf[ BUFFER_SIZE ];
  static int          ctot = 1;
  static int          utot = 1;

  unsigned short len = *( unsigned short * ) ( tickBuffer_.data() );
  comp               = len & 0x8000;
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
    if ( csize != 0 )
    {
      std::memcpy( buf, tickBuffer_.data() + 2, csize );
    }
  }

  utot += csize;

  // lastn = -1; // reset sv_setmap

  while ( idx < csize )
  {
    int retVal = processServerCommand( buf + idx );
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

int TickBuffer::processServerCommand( const std::uint8_t *bufferStart )
{
  ServerMessages::MessageTypes msgType = ServerMessages::getType( bufferStart[ 0 ] );
  std::cout << "Server message: " << ServerMessages::getName( msgType ) << std::endl;
  return 16;

  // if ( ServerMessages::getValue( msgType ) & ServerMessages::getValue( ServerMessages::MessageTypes::SETMAP ) )
  // {
  //   return sv_setmap( buf, buf[ 0 ] & ~ServerMessages::getValue( ServerMessages::MessageTypes::SETMAP ) );
  // }

  // switch ( msgType )
  // {
  // case ServerMessages::MessageTypes::SETCHAR_NAME1:
  //   sv_setchar_name1( buf );
  //   break;
  // case ServerMessages::MessageTypes::SETCHAR_NAME2:
  //   sv_setchar_name2( buf );
  //   break;
  // case ServerMessages::MessageTypes::SETCHAR_NAME3:
  //   sv_setchar_name3( buf );
  //   break;
  // case ServerMessages::MessageTypes::SETCHAR_MODE:
  //   sv_setchar_mode( buf );
  //   return 2;
  // case ServerMessages::MessageTypes::SETCHAR_ATTRIB:
  //   sv_setchar_attrib( buf );
  //   return 8;
  // case ServerMessages::MessageTypes::SETCHAR_SKILL:
  //   sv_setchar_skill( buf );
  //   return 8;
  // case ServerMessages::MessageTypes::SETCHAR_HP:
  //   sv_setchar_hp( buf );
  //   return 13;
  // case ServerMessages::MessageTypes::SETCHAR_ENDUR:
  //   sv_setchar_endur( buf );
  //   return 13;
  // case ServerMessages::MessageTypes::SETCHAR_MANA:
  //   sv_setchar_mana( buf );
  //   return 13;
  // case ServerMessages::MessageTypes::SETCHAR_AHP:
  //   sv_setchar_ahp( buf );
  //   return 3;
  // case ServerMessages::MessageTypes::SETCHAR_AEND:
  //   sv_setchar_aend( buf );
  //   return 3;
  // case ServerMessages::MessageTypes::SETCHAR_AMANA:
  //   sv_setchar_amana( buf );
  //   return 3;
  // case ServerMessages::MessageTypes::SETCHAR_DIR:
  //   sv_setchar_dir( buf );
  //   return 2;
  // case ServerMessages::MessageTypes::SETCHAR_PTS:
  //   sv_setchar_pts( buf );
  //   return 13;
  // case ServerMessages::MessageTypes::SETCHAR_GOLD:
  //   sv_setchar_gold( buf );
  //   return 13;
  // case ServerMessages::MessageTypes::SETCHAR_ITEM:
  //   sv_setchar_item( buf );
  //   return 9;
  // case ServerMessages::MessageTypes::SETCHAR_WORN:
  //   sv_setchar_worn( buf );
  //   return 9;
  // case ServerMessages::MessageTypes::SETCHAR_SPELL:
  //   sv_setchar_spell( buf );
  //   return 9;
  // case ServerMessages::MessageTypes::SETCHAR_OBJ:
  //   sv_setchar_obj( buf );
  //   return 5;
  // case ServerMessages::MessageTypes::SETMAP3:
  //   return sv_setmap3( buf, 26 );
  // case ServerMessages::MessageTypes::SETMAP4:
  //   return sv_setmap3( buf, 0 );
  // case ServerMessages::MessageTypes::SETMAP5:
  //   return sv_setmap3( buf, 2 );
  // case ServerMessages::MessageTypes::SETMAP6:
  //   return sv_setmap3( buf, 6 );
  // case ServerMessages::MessageTypes::SETORIGIN:
  //   sv_setorigin( buf );
  //   return 5;
  // case ServerMessages::MessageTypes::TICK:
  //   sv_tick( buf );
  //   return 2;
  // case ServerMessages::MessageTypes::LOG0:
  //   sv_log( buf, 0 );
  //   break;
  // case ServerMessages::MessageTypes::LOG1:
  //   sv_log( buf, 1 );
  //   break;
  // case ServerMessages::MessageTypes::LOG2:
  //   sv_log( buf, 2 );
  //   break;
  // case ServerMessages::MessageTypes::LOG3:
  //   sv_log( buf, 3 );
  //   break;
  // case ServerMessages::MessageTypes::SCROLL_RIGHT:
  //   sv_scroll_right( buf );
  //   return 1;
  // case ServerMessages::MessageTypes::SCROLL_LEFT:
  //   sv_scroll_left( buf );
  //   return 1;
  // case ServerMessages::MessageTypes::SCROLL_DOWN:
  //   sv_scroll_down( buf );
  //   return 1;
  // case ServerMessages::MessageTypes::SCROLL_UP:
  //   sv_scroll_up( buf );
  //   return 1;
  // case ServerMessages::MessageTypes::SCROLL_RIGHTDOWN:
  //   sv_scroll_rightdown( buf );
  //   return 1;
  // case ServerMessages::MessageTypes::SCROLL_RIGHTUP:
  //   sv_scroll_rightup( buf );
  //   return 1;
  // case ServerMessages::MessageTypes::SCROLL_LEFTDOWN:
  //   sv_scroll_leftdown( buf );
  //   return 1;
  // case ServerMessages::MessageTypes::SCROLL_LEFTUP:
  //   sv_scroll_leftup( buf );
  //   return 1;
  // case ServerMessages::MessageTypes::LOOK1:
  //   sv_look1( buf );
  //   break;
  // case ServerMessages::MessageTypes::LOOK2:
  //   sv_look2( buf );
  //   break;
  // case ServerMessages::MessageTypes::LOOK3:
  //   sv_look3( buf );
  //   break;
  // case ServerMessages::MessageTypes::LOOK4:
  //   sv_look4( buf );
  //   break;
  // case ServerMessages::MessageTypes::LOOK5:
  //   sv_look5( buf );
  //   break;
  // case ServerMessages::MessageTypes::LOOK6:
  //   sv_look6( buf );
  //   break;
  // case ServerMessages::MessageTypes::SETTARGET:
  //   sv_settarget( buf );
  //   return 13;
  // case ServerMessages::MessageTypes::PLAYSOUND:
  //   sv_playsound( buf );
  //   return 13;
  // case ServerMessages::MessageTypes::EXIT:
  //   sv_exit( buf );
  //   break;
  // case ServerMessages::MessageTypes::LOAD:
  //   sv_load( buf );
  //   return 5;
  // case ServerMessages::MessageTypes::UNIQUE:
  //   sv_unique( buf );
  //   return 9;
  // case ServerMessages::MessageTypes::IGNORE:
  //   return sv_ignore( buf );

  // case ServerMessages::MessageTypes::EMPTY:
  // case ServerMessages::MessageTypes::CHALLENGE:
  // case ServerMessages::MessageTypes::NEWPLAYER:
  // case ServerMessages::MessageTypes::LOGIN_OK:
  // case ServerMessages::MessageTypes::SETMAP2:
  // case ServerMessages::MessageTypes::MSG:
  // case ServerMessages::MessageTypes::CAP:
  // case ServerMessages::MessageTypes::MOD1:
  // case ServerMessages::MessageTypes::MOD2:
  // case ServerMessages::MessageTypes::MOD3:
  // case ServerMessages::MessageTypes::MOD4:
  // case ServerMessages::MessageTypes::MOD5:
  // case ServerMessages::MessageTypes::MOD6:
  // case ServerMessages::MessageTypes::MOD7:
  // case ServerMessages::MessageTypes::MOD8:
  // case ServerMessages::MessageTypes::SETMAP:

  // default:
  //   std::cerr << "Unknown server message type!" << std::endl;
  //   return -1;
  // }

  // return 16;
}