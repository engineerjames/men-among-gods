#include "TickBuffer.h"

#include <cstring>

#include "ClientTypes.h"
#include "ConstantIdentifiers.h"
#include "Logger.h"
#include "Map.h"
#include "PlayerData.h"
#include "ServerMessage.h"

TickBuffer::TickBuffer( PlayerData& playerData, MenAmongGods::Map& map )
    : compressor_()
    , playerData_( playerData )
    , map_( map )
    , tickBuffer_()
    , tickSize_( 0 )
    , tickStart_( 0 )
    , ticksInQueue_( 0 )
    , ctick_( 0 )
    , lastn_( 0 )
{
}

std::uint8_t* TickBuffer::getBufferStart() noexcept
{
  return &tickBuffer_.at( tickSize_ );
}

std::size_t TickBuffer::getAvailableBytes() noexcept
{
  return TickBuffer::TSIZE - tickSize_;
}

bool TickBuffer::receive( const std::array< std::uint8_t, 1024 >* buffer, std::size_t bytesToReceive )
{
  std::memcpy( getBufferStart(), buffer->data(), bytesToReceive );
  tickSize_ += bytesToReceive;

  if ( tickSize_ >= tickStart_ + 2 )
  {
    int tmp = *( unsigned short* ) ( tickBuffer_.data() + tickStart_ );
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

  static std::array< std::uint8_t, BUFFER_SIZE > buf {};
  static int                                     ctot = 1;
  static int                                     utot = 1;

  unsigned short len = *( unsigned short* ) ( tickBuffer_.data() );
  comp               = len & 0x8000;
  len &= 0x7fff;
  ctot += len;
  if ( len > tickSize_ )
  {
    return;
  }

  if ( comp )
  {
    compressor_.setNextInput( tickBuffer_.data() + 2 );
    compressor_.setAvailableIn( len - 2 );

    compressor_.setNextOutput( buf.data() );
    compressor_.setAvailableOut( BUFFER_SIZE );

    int ret = compressor_.inflate();

    if ( ret != Z_OK )
    {
      LOG_ERROR( "Uncompress error: " << ret );
    }

    if ( compressor_.getAvailableIn() != 0 )
    {
      LOG_ERROR( "uncompress: avail is " << compressor_.getAvailableIn() );
    }

    csize = static_cast< int >( BUFFER_SIZE ) - static_cast< int >( compressor_.getAvailableOut() );
  }
  else
  {
    csize = len - 2;
    if ( csize != 0 )
    {
      std::memcpy( buf.data(), tickBuffer_.data() + 2, csize );
    }
  }

  utot += csize;

  lastn_ = -1; // reset sv_setmap
  ctick_++;
  if ( ctick_ > 19 )
  {
    ctick_ = 0;
  }
  map_.setCTick( ctick_ );

  while ( idx < csize )
  {
    playerData_.lock();
    int retVal = processServerCommand( buf.data() + idx );
    playerData_.unlock();

    if ( retVal == -1 )
    {
      LOG_ERROR( "Warning: syntax error in server data" );
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

  // Was engine_tick before
  map_.tick();
}

int TickBuffer::processServerCommand( const std::uint8_t* bufferStart )
{
  ServerMessages::MessageTypes msgType = ServerMessages::getType( bufferStart[ 0 ] );

  std::uint8_t setMapValue = ServerMessages::getValue( ServerMessages::MessageTypes::SETMAP );
  if ( ServerMessages::getValue( msgType ) & setMapValue )
  {
    return sv_setmap( bufferStart, bufferStart[ 0 ] & ~setMapValue );
  }

  switch ( msgType )
  {
  case ServerMessages::MessageTypes::SETCHAR_NAME1:
    sv_setchar_name1( bufferStart );
    break;
  case ServerMessages::MessageTypes::SETCHAR_NAME2:
    sv_setchar_name2( bufferStart );
    break;
  case ServerMessages::MessageTypes::SETCHAR_NAME3:
    sv_setchar_name3( bufferStart );
    break;
  case ServerMessages::MessageTypes::SETCHAR_MODE:
    sv_setchar_mode( bufferStart );
    return 2;
  case ServerMessages::MessageTypes::SETCHAR_ATTRIB:
    sv_setchar_attrib( bufferStart );
    return 8;
  case ServerMessages::MessageTypes::SETCHAR_SKILL:
    sv_setchar_skill( bufferStart );
    return 8;
  case ServerMessages::MessageTypes::SETCHAR_HP:
    sv_setchar_hp( bufferStart );
    return 13;
  case ServerMessages::MessageTypes::SETCHAR_ENDUR:
    sv_setchar_endur( bufferStart );
    return 13;
  case ServerMessages::MessageTypes::SETCHAR_MANA:
    sv_setchar_mana( bufferStart );
    return 13;
  case ServerMessages::MessageTypes::SETCHAR_AHP:
    sv_setchar_ahp( bufferStart );
    return 3;
  case ServerMessages::MessageTypes::SETCHAR_AEND:
    sv_setchar_aend( bufferStart );
    return 3;
  case ServerMessages::MessageTypes::SETCHAR_AMANA:
    sv_setchar_amana( bufferStart );
    return 3;
  case ServerMessages::MessageTypes::SETCHAR_DIR:
    sv_setchar_dir( bufferStart );
    return 2;
  case ServerMessages::MessageTypes::SETCHAR_PTS:
    sv_setchar_pts( bufferStart );
    return 13;
  case ServerMessages::MessageTypes::SETCHAR_GOLD:
    sv_setchar_gold( bufferStart );
    return 13;
  case ServerMessages::MessageTypes::SETCHAR_ITEM:
    sv_setchar_item( bufferStart );
    return 9;
  case ServerMessages::MessageTypes::SETCHAR_WORN:
    sv_setchar_worn( bufferStart );
    return 9;
  case ServerMessages::MessageTypes::SETCHAR_SPELL:
    sv_setchar_spell( bufferStart );
    return 9;
  case ServerMessages::MessageTypes::SETCHAR_OBJ:
    sv_setchar_obj( bufferStart );
    return 5;
  case ServerMessages::MessageTypes::SETMAP3:
    return sv_setmap3( bufferStart, 26 );
  case ServerMessages::MessageTypes::SETMAP4:
    return sv_setmap3( bufferStart, 0 );
  case ServerMessages::MessageTypes::SETMAP5:
    return sv_setmap3( bufferStart, 2 );
  case ServerMessages::MessageTypes::SETMAP6:
    return sv_setmap3( bufferStart, 6 );
  case ServerMessages::MessageTypes::SETORIGIN:
    sv_setorigin( bufferStart );
    return 5;
  case ServerMessages::MessageTypes::TICK:
    sv_tick( bufferStart );
    return 2;
  case ServerMessages::MessageTypes::LOG0:
    sv_log( bufferStart, 0 );
    break;
  case ServerMessages::MessageTypes::LOG1:
    sv_log( bufferStart, 1 );
    break;
  case ServerMessages::MessageTypes::LOG2:
    sv_log( bufferStart, 2 );
    break;
  case ServerMessages::MessageTypes::LOG3:
    sv_log( bufferStart, 3 );
    break;
  case ServerMessages::MessageTypes::SCROLL_RIGHT:
    sv_scroll_right( bufferStart );
    return 1;
  case ServerMessages::MessageTypes::SCROLL_LEFT:
    sv_scroll_left( bufferStart );
    return 1;
  case ServerMessages::MessageTypes::SCROLL_DOWN:
    sv_scroll_down( bufferStart );
    return 1;
  case ServerMessages::MessageTypes::SCROLL_UP:
    sv_scroll_up( bufferStart );
    return 1;
  case ServerMessages::MessageTypes::SCROLL_RIGHTDOWN:
    sv_scroll_rightdown( bufferStart );
    return 1;
  case ServerMessages::MessageTypes::SCROLL_RIGHTUP:
    sv_scroll_rightup( bufferStart );
    return 1;
  case ServerMessages::MessageTypes::SCROLL_LEFTDOWN:
    sv_scroll_leftdown( bufferStart );
    return 1;
  case ServerMessages::MessageTypes::SCROLL_LEFTUP:
    sv_scroll_leftup( bufferStart );
    return 1;
  case ServerMessages::MessageTypes::LOOK1:
    sv_look1( bufferStart );
    break;
  case ServerMessages::MessageTypes::LOOK2:
    sv_look2( bufferStart );
    break;
  case ServerMessages::MessageTypes::LOOK3:
    sv_look3( bufferStart );
    break;
  case ServerMessages::MessageTypes::LOOK4:
    sv_look4( bufferStart );
    break;
  case ServerMessages::MessageTypes::LOOK5:
    sv_look5( bufferStart );
    break;
  case ServerMessages::MessageTypes::LOOK6:
    sv_look6( bufferStart );
    break;
  case ServerMessages::MessageTypes::SETTARGET:
    sv_settarget( bufferStart );
    return 13;
  case ServerMessages::MessageTypes::PLAYSOUND:
    sv_playsound( bufferStart );
    return 13;
  case ServerMessages::MessageTypes::EXIT:
    sv_exit( bufferStart );
    break;
  case ServerMessages::MessageTypes::LOAD:
    sv_load( bufferStart );
    return 5;
  case ServerMessages::MessageTypes::UNIQUE:
    sv_unique( bufferStart );
    return 9;
  case ServerMessages::MessageTypes::IGNORE:
    return sv_ignore( bufferStart );

  case ServerMessages::MessageTypes::EMPTY:
  case ServerMessages::MessageTypes::CHALLENGE:
  case ServerMessages::MessageTypes::NEWPLAYER:
  case ServerMessages::MessageTypes::LOGIN_OK:
  case ServerMessages::MessageTypes::SETMAP2:
  case ServerMessages::MessageTypes::MSG:
  case ServerMessages::MessageTypes::CAP:
  case ServerMessages::MessageTypes::MOD1:
  case ServerMessages::MessageTypes::MOD2:
  case ServerMessages::MessageTypes::MOD3:
  case ServerMessages::MessageTypes::MOD4:
  case ServerMessages::MessageTypes::MOD5:
  case ServerMessages::MessageTypes::MOD6:
  case ServerMessages::MessageTypes::MOD7:
  case ServerMessages::MessageTypes::MOD8:
  case ServerMessages::MessageTypes::SETMAP:
  default:
    LOG_ERROR( "Unknown server message type!" );
    return -1;
  }

  return 16;
}

const std::array< const char*, 15 > logout_reason = {
    "unknown",                                                                              // 0
    "Client failed challenge.",                                                             // 1
    "Client was idle too long.",                                                            // 2
    "No room to drop character.",                                                           // 3
    "Invalid parameters.",                                                                  // 4
    "Character already active or no player character.",                                     // 5
    "Invalid password.",                                                                    // 6
    "Client too slow.",                                                                     // 7
    "Receive failure.",                                                                     // 8
    "Server is being shutdown.",                                                            // 9
    "You entered a Tavern.",                                                                // 10
    "Client version too old. Update needed.",                                               // 11
    "Aborting on user request.",                                                            // 12
    "this should never show up",                                                            // 13
    "You have been banned for an hour. Enhance your social behaviour before you come back." // 14
};

void TickBuffer::sv_setchar_name1( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_name1" );
  std::memcpy( playerData_.getClientSidePlayerInfo().name, buf + 1, 15 );
}

void TickBuffer::sv_setchar_name2( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_name2" );
  std::memcpy( playerData_.getClientSidePlayerInfo().name + 15, buf + 1, 15 );
}

void TickBuffer::sv_setchar_name3( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_name3" );
  std::memcpy( playerData_.getClientSidePlayerInfo().name + 30, buf + 1, 10 );

  playerData_.setOkeyName( playerData_.getClientSidePlayerInfo().name );
  playerData_.setRaceAndSex( *( unsigned long* ) ( buf + 11 ) );
  playerData_.saveToJsonFile();
}

void TickBuffer::sv_setchar_mode( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_mode" );
  playerData_.getClientSidePlayerInfo().mode = buf[ 1 ];
}

void TickBuffer::sv_setchar_hp( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_hp" );
  playerData_.getClientSidePlayerInfo().hp[ 0 ] = *( unsigned short* ) ( buf + 1 );
  playerData_.getClientSidePlayerInfo().hp[ 1 ] = *( unsigned short* ) ( buf + 3 );
  playerData_.getClientSidePlayerInfo().hp[ 2 ] = *( unsigned short* ) ( buf + 5 );
  playerData_.getClientSidePlayerInfo().hp[ 3 ] = *( unsigned short* ) ( buf + 7 );
  playerData_.getClientSidePlayerInfo().hp[ 4 ] = *( unsigned short* ) ( buf + 9 );
  playerData_.getClientSidePlayerInfo().hp[ 5 ] = *( unsigned short* ) ( buf + 11 );
}

void TickBuffer::sv_setchar_endur( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_endur" );
  playerData_.getClientSidePlayerInfo().end[ 0 ] = *( short int* ) ( buf + 1 );
  playerData_.getClientSidePlayerInfo().end[ 1 ] = *( short int* ) ( buf + 3 );
  playerData_.getClientSidePlayerInfo().end[ 2 ] = *( short int* ) ( buf + 5 );
  playerData_.getClientSidePlayerInfo().end[ 3 ] = *( short int* ) ( buf + 7 );
  playerData_.getClientSidePlayerInfo().end[ 4 ] = *( short int* ) ( buf + 9 );
  playerData_.getClientSidePlayerInfo().end[ 5 ] = *( short int* ) ( buf + 11 );
}

void TickBuffer::sv_setchar_mana( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_mana" );
  playerData_.getClientSidePlayerInfo().mana[ 0 ] = *( short int* ) ( buf + 1 );
  playerData_.getClientSidePlayerInfo().mana[ 1 ] = *( short int* ) ( buf + 3 );
  playerData_.getClientSidePlayerInfo().mana[ 2 ] = *( short int* ) ( buf + 5 );
  playerData_.getClientSidePlayerInfo().mana[ 3 ] = *( short int* ) ( buf + 7 );
  playerData_.getClientSidePlayerInfo().mana[ 4 ] = *( short int* ) ( buf + 9 );
  playerData_.getClientSidePlayerInfo().mana[ 5 ] = *( short int* ) ( buf + 11 );
}

void TickBuffer::sv_setchar_attrib( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_attrib" );
  int n = buf[ 1 ];

  if ( n < 0 || n > 4 )
    return;

  playerData_.getClientSidePlayerInfo().attrib[ n ][ 0 ] = buf[ 2 ];
  playerData_.getClientSidePlayerInfo().attrib[ n ][ 1 ] = buf[ 3 ];
  playerData_.getClientSidePlayerInfo().attrib[ n ][ 2 ] = buf[ 4 ];
  playerData_.getClientSidePlayerInfo().attrib[ n ][ 3 ] = buf[ 5 ];
  playerData_.getClientSidePlayerInfo().attrib[ n ][ 4 ] = buf[ 6 ];
  playerData_.getClientSidePlayerInfo().attrib[ n ][ 5 ] = buf[ 7 ];
}

void TickBuffer::sv_setchar_skill( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_skill" );

  int n = buf[ 1 ];
  if ( n < 0 || n > 49 )
    return;

  playerData_.getClientSidePlayerInfo().skill[ n ][ 0 ] = buf[ 2 ];
  playerData_.getClientSidePlayerInfo().skill[ n ][ 1 ] = buf[ 3 ];
  playerData_.getClientSidePlayerInfo().skill[ n ][ 2 ] = buf[ 4 ];
  playerData_.getClientSidePlayerInfo().skill[ n ][ 3 ] = buf[ 5 ];
  playerData_.getClientSidePlayerInfo().skill[ n ][ 4 ] = buf[ 6 ];
  playerData_.getClientSidePlayerInfo().skill[ n ][ 5 ] = buf[ 7 ];

  playerData_.sortSkills();
}

void TickBuffer::sv_setchar_ahp( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_ahp" );
  playerData_.getClientSidePlayerInfo().a_hp = *( unsigned short* ) ( buf + 1 );
}

void TickBuffer::sv_setchar_aend( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_aend" );
  playerData_.getClientSidePlayerInfo().a_end = *( unsigned short* ) ( buf + 1 );
}

void TickBuffer::sv_setchar_amana( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_amana" );
  playerData_.getClientSidePlayerInfo().a_mana = *( unsigned short* ) ( buf + 1 );
}

void TickBuffer::sv_setchar_dir( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_dir" );
  playerData_.getClientSidePlayerInfo().dir = *( unsigned char* ) ( buf + 1 );
}

void TickBuffer::sv_setchar_pts( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_pts" );
  playerData_.getClientSidePlayerInfo().points     = *( unsigned long* ) ( buf + 1 );
  playerData_.getClientSidePlayerInfo().points_tot = *( unsigned long* ) ( buf + 5 );
  playerData_.getClientSidePlayerInfo().kindred    = *( unsigned long* ) ( buf + 9 );
}

void TickBuffer::sv_setchar_gold( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_gold" );
  playerData_.getClientSidePlayerInfo().gold   = *( unsigned long* ) ( buf + 1 );
  playerData_.getClientSidePlayerInfo().armor  = *( unsigned long* ) ( buf + 5 );
  playerData_.getClientSidePlayerInfo().weapon = *( unsigned long* ) ( buf + 9 );
}

void TickBuffer::sv_setchar_item( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_item" );

  int n = *( unsigned long* ) ( buf + 1 );
  if ( n < 0 || n > 39 )
  {
    LOG_ERROR( "Invalid setchar item" );
  }
  playerData_.getClientSidePlayerInfo().item[ n ]   = *( short int* ) ( buf + 5 );
  playerData_.getClientSidePlayerInfo().item_p[ n ] = *( short int* ) ( buf + 7 );
}

void TickBuffer::sv_setchar_worn( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_worn" );

  int n = *( unsigned long* ) ( buf + 1 );
  if ( n < 0 || n > 19 )
  {
    LOG_ERROR( "Invalid setchar worn" );
  }
  playerData_.getClientSidePlayerInfo().worn[ n ]   = *( short int* ) ( buf + 5 );
  playerData_.getClientSidePlayerInfo().worn_p[ n ] = *( short int* ) ( buf + 7 );
}

void TickBuffer::sv_setchar_spell( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_spell" );

  int n = *( unsigned long* ) ( buf + 1 );
  if ( n < 0 || n > 19 )
  {
    LOG_ERROR( "Invalid setchar spell" );
  }
  playerData_.getClientSidePlayerInfo().spell[ n ]  = *( short int* ) ( buf + 5 );
  playerData_.getClientSidePlayerInfo().active[ n ] = *( short int* ) ( buf + 7 );
}

void TickBuffer::sv_setchar_obj( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setchar_obj" );

  playerData_.getClientSidePlayerInfo().citem   = *( short int* ) ( buf + 1 );
  playerData_.getClientSidePlayerInfo().citem_p = *( short int* ) ( buf + 3 );
}

int TickBuffer::sv_setmap( const unsigned char* buf, int off )
{
  LOG_DEBUG( "TickBuffer::sv_setmap" );

  int                         n {};
  int                         p {};
  static std::array< int, 8 > cnt {};

  if ( off )
  {
    n = lastn_ + off;
    p = 2;
  }
  else
  {
    n = *( unsigned short* ) ( buf + 2 );
    p = 4;
  }

  if ( n < 0 || n >= TILEX * TILEY )
  {
    LOG_ERROR( "Corrupt setmap!" );

    return -1;
  }

  lastn_ = n;
  if ( ! buf[ 1 ] )
  {
    LOG_ERROR( "Warning: no flags in setmap!" );

    return -1;
  }

  if ( buf[ 1 ] & 1 )
  {
    map_.setBackgroundSprite( n, *( unsigned short* ) ( buf + p ) );
    p += 2;
    cnt[ 0 ]++;
  }
  if ( buf[ 1 ] & 2 )
  {
    map_.setFlags( n, *( unsigned int* ) ( buf + p ) );
    p += 4;
    cnt[ 1 ]++;
  }
  if ( buf[ 1 ] & 4 )
  {
    map_.setFlags2( n, *( unsigned int* ) ( buf + p ) );
    p += 4;
    cnt[ 2 ]++;
  }
  if ( buf[ 1 ] & 8 )
  {
    map_.setItemSprite( n, *( unsigned short* ) ( buf + p ) );
    p += 2;
    cnt[ 3 ]++;
  }
  if ( buf[ 1 ] & 16 )
  {
    map_.setItemStatus( n, *( unsigned char* ) ( buf + p ) );
    p += 1;
    cnt[ 4 ]++;
  }
  if ( buf[ 1 ] & 32 )
  {
    map_.setCharacterSprite( n, *( unsigned short* ) ( buf + p ) );
    p += 2;
    map_.setCharacterStatus( n, *( unsigned char* ) ( buf + p ) );
    p += 1;
    map_.setCharacterStatOff( n, *( unsigned char* ) ( buf + p ) );
    p += 1;
    cnt[ 5 ]++;
  }
  if ( buf[ 1 ] & 64 )
  {
    map_.setCharacterId( n, *( unsigned short* ) ( buf + p ) );
    p += 2;
    map_.setCharacterCrc( n, *( unsigned short* ) ( buf + p ) );
    p += 2;
    map_.setCharacterSpeed( n, *( unsigned char* ) ( buf + p ) );
    p += 1;
    cnt[ 6 ]++;
  }
  if ( buf[ 1 ] & 128 )
  {
    map_.setCharacterPercentHealth( n, *( unsigned char* ) ( buf + p ) );
    p += 1;
    cnt[ 7 ]++;
  }

  return p;
}

int TickBuffer::sv_setmap3( const unsigned char* buf, int cnt )
{
  LOG_DEBUG( "TickBuffer::sv_setmap3" );

  int m {};
  int p {};

  int            n   = ( *( unsigned short* ) ( buf + 1 ) ) & 2047;
  unsigned short tmp = ( *( unsigned short* ) ( buf + 1 ) ) >> 12;
  if ( n < 0 || n >= TILEX * TILEY )
  {
    LOG_ERROR( "corrupt setmap3!" );
    return -1;
  }

  map_.setLight( n, tmp );

  for ( m = n + 2, p = 3; m < n + cnt + 2; m += 2, p++ )
  {
    if ( m < TILEX * TILEY )
    {
      tmp = *( unsigned char* ) ( buf + p );

      map_.setLight( m, ( unsigned char ) ( tmp & 15 ) );
      map_.setLight( m - 1, ( unsigned char ) ( tmp >> 4 ) );
    }
  }

  return p;
}

void TickBuffer::sv_setorigin( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_setorigin" );

  int x {};
  int y {};
  int xp {};
  int yp {};
  int n {};

  xp = *( short* ) ( buf + 1 );
  yp = *( short* ) ( buf + 3 );

  for ( y = n = 0; y < TILEY; y++ )
  {
    for ( x = 0; x < TILEX; x++, n++ )
    {
      map_.setX( n, ( unsigned short ) ( x + xp ) );
      map_.setY( n, ( unsigned short ) ( y + yp ) );
    }
  }
}

void TickBuffer::sv_tick( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_tick" );

  ctick_ = *( unsigned char* ) ( buf + 1 );
  map_.setCTick( ctick_ );
}

void TickBuffer::sv_log( const unsigned char* buf, int font )
{
  LOG_DEBUG( "TickBuffer::sv_log" );

  static std::array< char, 512 > text {};
  static int                     cnt = 0;
  int                            n {};

  std::memcpy( text.data() + cnt, buf + 1, 15 );

  for ( n = cnt; n < cnt + 15; n++ )
    if ( text[ n ] == 10 )
    {
      text[ n ] = 0;

      playerData_.addLogMessage( getLogType( font ), text.data() );
      cnt = 0;
      return;
    }
  cnt += 15;

  if ( cnt > 500 )
  {
    LOG_ERROR( "sv_log(): cnt too big!" );

    text[ cnt ] = 0;
    cnt         = 0;
  }
}

void TickBuffer::sv_scroll_right( const unsigned char* )
{
  LOG_DEBUG( "TickBuffer::sv_scroll_right" );
  map_.scrollRight();
}

void TickBuffer::sv_scroll_left( const unsigned char* )
{
  LOG_DEBUG( "TickBuffer::sv_scroll_left" );
  map_.scrollLeft();
}

void TickBuffer::sv_scroll_down( const unsigned char* )
{
  LOG_DEBUG( "TickBuffer::sv_scroll_down" );
  map_.scrollDown();
}

void TickBuffer::sv_scroll_up( const unsigned char* )
{
  LOG_DEBUG( "TickBuffer::sv_scroll_up" );
  map_.scrollUp();
}

void TickBuffer::sv_scroll_leftup( const unsigned char* )
{
  LOG_DEBUG( "TickBuffer::sv_scroll_leftup" );
  map_.scrollLeftUp();
}

void TickBuffer::sv_scroll_leftdown( const unsigned char* )
{
  LOG_DEBUG( "TickBuffer::sv_scroll_leftdown" );
  map_.scrollLeftDown();
}

void TickBuffer::sv_scroll_rightup( const unsigned char* )
{
  LOG_DEBUG( "TickBuffer::sv_scroll_rightup" );
  map_.scrollRightUp();
}

void TickBuffer::sv_scroll_rightdown( const unsigned char* )
{
  LOG_DEBUG( "TickBuffer::sv_scroll_rightdown" );
  map_.scrollRightDown();
}

void TickBuffer::sv_look1( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_look1" );

  playerData_.getLook().worn[ 0 ] = *( unsigned short* ) ( buf + 1 );
  playerData_.getLook().worn[ 2 ] = *( unsigned short* ) ( buf + 3 );
  playerData_.getLook().worn[ 3 ] = *( unsigned short* ) ( buf + 5 );
  playerData_.getLook().worn[ 5 ] = *( unsigned short* ) ( buf + 7 );
  playerData_.getLook().worn[ 6 ] = *( unsigned short* ) ( buf + 9 );
  playerData_.getLook().worn[ 7 ] = *( unsigned short* ) ( buf + 11 );
  playerData_.getLook().worn[ 8 ] = *( unsigned short* ) ( buf + 13 );
  playerData_.getLook().autoflag  = *( unsigned char* ) ( buf + 15 );
}

void TickBuffer::sv_look2( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_look2" );

  playerData_.getLook().worn[ 9 ]  = *( unsigned short* ) ( buf + 1 );  // 1 2
  playerData_.getLook().sprite     = *( unsigned short* ) ( buf + 3 );  // 3 4
  playerData_.getLook().points     = *( unsigned int* ) ( buf + 5 );    // 5 6 7 8
  playerData_.getLook().hp         = *( unsigned int* ) ( buf + 9 );    // 9 10 11 12
  playerData_.getLook().worn[ 10 ] = *( unsigned short* ) ( buf + 13 ); // 13 14
}

void TickBuffer::sv_look3( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_look3" );

  playerData_.getLook().end    = *( unsigned short* ) ( buf + 1 );
  playerData_.getLook().a_hp   = *( unsigned short* ) ( buf + 3 );
  playerData_.getLook().a_end  = *( unsigned short* ) ( buf + 5 );
  playerData_.getLook().nr     = *( unsigned short* ) ( buf + 7 );
  playerData_.getLook().id     = *( unsigned short* ) ( buf + 9 );
  playerData_.getLook().mana   = *( unsigned short* ) ( buf + 11 );
  playerData_.getLook().a_mana = *( unsigned short* ) ( buf + 13 );
}

void TickBuffer::sv_look4( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_look4" );

  playerData_.getLook().worn[ 1 ]  = *( unsigned short* ) ( buf + 1 );
  playerData_.getLook().worn[ 4 ]  = *( unsigned short* ) ( buf + 3 );
  playerData_.getLook().extended   = buf[ 5 ];
  playerData_.getLook().pl_price   = *( unsigned int* ) ( buf + 6 );
  playerData_.getLook().worn[ 11 ] = *( unsigned short* ) ( buf + 10 );
  playerData_.getLook().worn[ 12 ] = *( unsigned short* ) ( buf + 12 );
  playerData_.getLook().worn[ 13 ] = *( unsigned short* ) ( buf + 14 );
}

void TickBuffer::sv_look5( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_look5" );

  for ( int n = 0; n < 15; n++ )
  {
    playerData_.getLook().name[ n ] = buf[ n + 1 ];
  }

  playerData_.getLook().name[ 15 ] = 0;

  if ( ! playerData_.getLook().extended )
  {
    if ( ! playerData_.getLook().autoflag )
    {
      playerData_.setShowLook( true );
      // look_timer = 10 * TICKS;
    }
    playerData_.add_look( playerData_.getLook().nr, playerData_.getLook().name, playerData_.getLook().id );
  }
}

void TickBuffer::sv_look6( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_look6" );

  int n {};
  int s {};

  s = buf[ 1 ];

  for ( n = s; n < std::min( 62, s + 2 ); n++ )
  {
    playerData_.getLook().item[ n ]  = *( unsigned short* ) ( buf + 2 + ( n - s ) * 6 );
    playerData_.getLook().price[ n ] = *( unsigned int* ) ( buf + 4 + ( n - s ) * 6 );
  }
  if ( n == 62 )
  {
    playerData_.setShouldShowShop( true );
    playerData_.setShopOnCurrentLook();
  }
}

void TickBuffer::sv_settarget( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_settarget" );

  playerData_.getClientSidePlayerInfo().attack_cn    = *( unsigned short* ) ( buf + 1 );
  playerData_.getClientSidePlayerInfo().goto_x       = *( unsigned short* ) ( buf + 3 );
  playerData_.getClientSidePlayerInfo().goto_y       = *( unsigned short* ) ( buf + 5 );
  playerData_.getClientSidePlayerInfo().misc_action  = *( unsigned short* ) ( buf + 7 );
  playerData_.getClientSidePlayerInfo().misc_target1 = *( unsigned short* ) ( buf + 9 );
  playerData_.getClientSidePlayerInfo().misc_target2 = *( unsigned short* ) ( buf + 11 );
}

void TickBuffer::sv_playsound( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_playsound" );

  int                    nr {};
  int                    vol {};
  int                    pan {};
  std::array< char, 80 > name {};

  nr  = *( unsigned int* ) ( buf + 1 );
  vol = *( int* ) ( buf + 5 );
  pan = *( int* ) ( buf + 9 );

  ( void ) vol;
  ( void ) pan;
  sprintf( name.data(), "sfx\\%d.wav", nr );
  // play_sound(name, vol, -pan); // add flag to reverse channels!!
}

void TickBuffer::sv_exit( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_exit" );

  int reason = *( unsigned int* ) ( buf + 1 );

  if ( reason < 1 || reason > 12 )
  {
    LOG_ERROR( "EXIT: Reason unknown." );
  }
  else
  {
    LOG_ERROR( "EXIT: " << logout_reason[ reason ] );
  }
  // do_exit = 1;
}

void TickBuffer::sv_load( const unsigned char* )
{
  LOG_DEBUG( "TickBuffer::sv_load" );

  // int load <<--- EXTERN
  // load = *( unsigned int * ) ( buf + 1 ); // This is the server load; don't care about this
}

void TickBuffer::sv_unique( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_unique" );

  int unique1 = *( unsigned int* ) ( buf + 1 );
  int unique2 = *( unsigned int* ) ( buf + 5 );

  playerData_.setUnique1( unique1 );
  playerData_.setUnique2( unique2 );

  // save_unique
  playerData_.saveToJsonFile();
}

int TickBuffer::sv_ignore( const unsigned char* buf )
{
  LOG_DEBUG( "TickBuffer::sv_ignore" );

  int        size {};
  int        d {};
  static int cnt {};
  static int got {};
  static int start {};

  size = *( unsigned int* ) ( buf + 1 );
  got += size;

  if ( ! start )
  {
    start = static_cast< int >( time( NULL ) );
  }

  if ( cnt++ > 16 )
  {
    cnt = 0;
    d   = static_cast< int >( time( NULL ) - start );
    if ( d == 0 )
    {
      // NOLINTNEXTLINE
      d = 1;
    }
  }

  return size;
}