#include "TickBuffer.h"

#include <cstring>
#include <iostream>

#include "ConstantIdentifiers.h"
#include "ServerMessage.h"

// Temporary global -- delete ASAP
cplayer pl {};
look tmplook{};
key okey{};
cmap* map = new cmap[5000]();
skilltab* playerSkillTab = new skilltab[500]();
unsigned int ctick = 0;

// Declarations to eliminate after refactoring

void sv_setchar_name1(const unsigned char *buf);
void sv_setchar_name2(const unsigned char *buf);
void sv_setchar_name3(const unsigned char *buf);
void sv_setchar_mode(const unsigned char *buf);
void sv_setchar_hp(const unsigned char *buf);
void sv_setchar_endur(const unsigned char *buf);
void sv_setchar_mana(const unsigned char *buf);
void sv_setchar_attrib(const unsigned char *buf);
void sv_setchar_skill(const unsigned char *buf);
void sv_setchar_ahp(const unsigned char *buf);
void sv_setchar_aend(const unsigned char *buf);
void sv_setchar_amana(const unsigned char *buf);
void sv_setchar_dir(const unsigned char *buf);
void sv_setchar_pts(const unsigned char *buf);
void sv_setchar_gold(const unsigned char *buf);
void sv_setchar_item(const unsigned char *buf);
void sv_setchar_worn(const unsigned char *buf);
void sv_setchar_spell(const unsigned char *buf);
void sv_setchar_obj(const unsigned char *buf);
int  sv_setmap(const unsigned char *buf, int off);
int  sv_setmap3(const unsigned char *buf, int cnt);
void sv_setorigin(const unsigned char *buf);
void sv_tick(const unsigned char *buf);
void sv_log(const unsigned char *buf, int font);
void sv_scroll_right(const unsigned char *buf);
void sv_scroll_left(const unsigned char *buf);
void sv_scroll_down(const unsigned char *buf);
void sv_scroll_up(const unsigned char *buf);
void sv_scroll_leftup(const unsigned char *buf);
void sv_scroll_leftdown(const unsigned char *buf);
void sv_scroll_rightup(const unsigned char *buf);
void sv_scroll_rightdown(const unsigned char *buf);
void sv_look1(const unsigned char *buf);
void sv_look2(const unsigned char *buf);
void sv_look3(const unsigned char *buf);
void sv_look4(const unsigned char *buf);
void sv_look5(const unsigned char *buf);
void sv_look6(const unsigned char *buf);
void sv_settarget(const unsigned char *buf);
void sv_playsound(const unsigned char *buf);
void sv_exit(const unsigned char *buf);
void sv_load(const unsigned char *buf);
void sv_unique(const unsigned char *buf);
int  sv_ignore(const unsigned char *buf);
int  skill_cmp(const void *a, const void *b);

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
     return;
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

  if ( ServerMessages::getValue( msgType ) & ServerMessages::getValue( ServerMessages::MessageTypes::SETMAP ) )
  {
    return sv_setmap( bufferStart, bufferStart[ 0 ] & ~ServerMessages::getValue( ServerMessages::MessageTypes::SETMAP ) );
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
    std::cerr << "Unknown server message type!" << std::endl;
    return -1;
  }

  return 16;
}

// Begin server message processing implementation
int skill_cmp( const void *a, const void *b )
{
  const skilltab *c, *d;
  int             m1, m2;

  c = static_cast< const skilltab * >( a );
  d = static_cast< const skilltab * >( b );

  m1 = c->nr;
  m2 = d->nr;

  if ( m1 == 99 && m2 != 99 )
    return 1;
  if ( m2 == 99 && m1 != 99 )
    return -1;

  if ( pl.skill[ m1 ][ 0 ] == 0 && pl.skill[ m2 ][ 0 ] != 0 )
    return 1;
  if ( pl.skill[ m2 ][ 0 ] == 0 && pl.skill[ m1 ][ 0 ] != 0 )
    return -1;

  if ( c->sortkey > d->sortkey )
    return 1;
  if ( c->sortkey < d->sortkey )
    return -1;

  return strcmp( c->name, d->name );
}

const char *logout_reason[] = {
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

void sv_setchar_name1( const unsigned char *buf )
{
  std::memcpy( pl.name, buf + 1, 15 );
}

void sv_setchar_name2( const unsigned char *buf )
{
  std::memcpy( pl.name + 15, buf + 1, 15 );
}

void sv_setchar_name3( const unsigned char *buf )
{
  std::memcpy( pl.name + 30, buf + 1, 10 );
  strcpy( okey.name, pl.name );
  okey.race = *( unsigned long * ) ( buf + 11 );
  // save_options();
}

void sv_setchar_mode( const unsigned char *buf )
{
  pl.mode = buf[ 1 ];
}

void sv_setchar_hp( const unsigned char *buf )
{
  pl.hp[ 0 ] = *( unsigned short * ) ( buf + 1 );
  pl.hp[ 1 ] = *( unsigned short * ) ( buf + 3 );
  pl.hp[ 2 ] = *( unsigned short * ) ( buf + 5 );
  pl.hp[ 3 ] = *( unsigned short * ) ( buf + 7 );
  pl.hp[ 4 ] = *( unsigned short * ) ( buf + 9 );
  pl.hp[ 5 ] = *( unsigned short * ) ( buf + 11 );
}

void sv_setchar_endur( const unsigned char *buf )
{
  pl.end[ 0 ] = *( short int * ) ( buf + 1 );
  pl.end[ 1 ] = *( short int * ) ( buf + 3 );
  pl.end[ 2 ] = *( short int * ) ( buf + 5 );
  pl.end[ 3 ] = *( short int * ) ( buf + 7 );
  pl.end[ 4 ] = *( short int * ) ( buf + 9 );
  pl.end[ 5 ] = *( short int * ) ( buf + 11 );
}

void sv_setchar_mana( const unsigned char *buf )
{
  pl.mana[ 0 ] = *( short int * ) ( buf + 1 );
  pl.mana[ 1 ] = *( short int * ) ( buf + 3 );
  pl.mana[ 2 ] = *( short int * ) ( buf + 5 );
  pl.mana[ 3 ] = *( short int * ) ( buf + 7 );
  pl.mana[ 4 ] = *( short int * ) ( buf + 9 );
  pl.mana[ 5 ] = *( short int * ) ( buf + 11 );
}

void sv_setchar_attrib( const unsigned char *buf )
{
  int n;

  n = buf[ 1 ];
  if ( n < 0 || n > 4 )
    return;

  pl.attrib[ n ][ 0 ] = buf[ 2 ];
  pl.attrib[ n ][ 1 ] = buf[ 3 ];
  pl.attrib[ n ][ 2 ] = buf[ 4 ];
  pl.attrib[ n ][ 3 ] = buf[ 5 ];
  pl.attrib[ n ][ 4 ] = buf[ 6 ];
  pl.attrib[ n ][ 5 ] = buf[ 7 ];
}

void sv_setchar_skill( const unsigned char *buf )
{
  int n;
  n = buf[ 1 ];
  if ( n < 0 || n > 49 )
    return;

  pl.skill[ n ][ 0 ] = buf[ 2 ];
  pl.skill[ n ][ 1 ] = buf[ 3 ];
  pl.skill[ n ][ 2 ] = buf[ 4 ];
  pl.skill[ n ][ 3 ] = buf[ 5 ];
  pl.skill[ n ][ 4 ] = buf[ 6 ];
  pl.skill[ n ][ 5 ] = buf[ 7 ];

  // TODO: Re-evaluate this
  qsort( playerSkillTab, 50, sizeof( skilltab ), skill_cmp );
}

void sv_setchar_ahp( const unsigned char *buf )
{
  pl.a_hp = *( unsigned short * ) ( buf + 1 );
}

void sv_setchar_aend( const unsigned char *buf )
{
  pl.a_end = *( unsigned short * ) ( buf + 1 );
}

void sv_setchar_amana( const unsigned char *buf )
{
  pl.a_mana = *( unsigned short * ) ( buf + 1 );
}

void sv_setchar_dir( const unsigned char *buf )
{
  pl.dir = *( unsigned char * ) ( buf + 1 );
}

void sv_setchar_pts( const unsigned char *buf )
{
  pl.points     = *( unsigned long * ) ( buf + 1 );
  pl.points_tot = *( unsigned long * ) ( buf + 5 );
  pl.kindred    = *( unsigned long * ) ( buf + 9 );
}

void sv_setchar_gold( const unsigned char *buf )
{
  pl.gold   = *( unsigned long * ) ( buf + 1 );
  pl.armor  = *( unsigned long * ) ( buf + 5 );
  pl.weapon = *( unsigned long * ) ( buf + 9 );
}

void sv_setchar_item( const unsigned char *buf )
{
  int n;

  n = *( unsigned long * ) ( buf + 1 );
  if ( n < 0 || n > 39 )
  {
    std::cerr << "Invalid setchar item" << std::endl;
  }
  pl.item[ n ]   = *( short int * ) ( buf + 5 );
  pl.item_p[ n ] = *( short int * ) ( buf + 7 );
}

void sv_setchar_worn( const unsigned char *buf )
{
  int n;

  n = *( unsigned long * ) ( buf + 1 );
  if ( n < 0 || n > 19 )
  {
    std::cerr << "Invalid setchar worn" << std::endl;
  }
  pl.worn[ n ]   = *( short int * ) ( buf + 5 );
  pl.worn_p[ n ] = *( short int * ) ( buf + 7 );
}

void sv_setchar_spell( const unsigned char *buf )
{
  int n;

  n = *( unsigned long * ) ( buf + 1 );
  if ( n < 0 || n > 19 )
  {
    std::cerr << "Invalid setchar spell" << std::endl;
  }
  pl.spell[ n ]  = *( short int * ) ( buf + 5 );
  pl.active[ n ] = *( short int * ) ( buf + 7 );
}

void sv_setchar_obj( const unsigned char *buf )
{
  pl.citem   = *( short int * ) ( buf + 1 );
  pl.citem_p = *( short int * ) ( buf + 3 );
}

static int lastn = 0;

int sv_setmap( const unsigned char *buf, int off )
{
  int        n, p;
  static int cnt[ 8 ] = { 0, 0, 0, 0, 0, 0, 0, 0 };

  if ( off )
  {
    n = lastn + off;
    p = 2;
  }
  else
  {
    n = *( unsigned short * ) ( buf + 2 );
    p = 4;
  }

  if ( n < 0 || n >= TILEX * TILEY )
  {
    std::cerr << "corrupt setmap!" << std::endl;
    return -1;
  }

  lastn = n;
  if ( ! buf[ 1 ] )
  {
    std::cerr << "Warning: no flags in setmap!" << std::endl;
    return -1;
  }

  if ( buf[ 1 ] & 1 )
  {
    map[ n ].ba_sprite = *( unsigned short * ) ( buf + p );
    p += 2;
    cnt[ 0 ]++;
  }
  if ( buf[ 1 ] & 2 )
  {
    map[ n ].flags = *( unsigned int * ) ( buf + p );
    p += 4;
    cnt[ 1 ]++;
  }
  if ( buf[ 1 ] & 4 )
  {
    map[ n ].flags2 = *( unsigned int * ) ( buf + p );
    p += 4;
    cnt[ 2 ]++;
  }
  if ( buf[ 1 ] & 8 )
  {
    map[ n ].it_sprite = *( unsigned short * ) ( buf + p );
    p += 2;
    cnt[ 3 ]++;
  }
  if ( buf[ 1 ] & 16 )
  {
    map[ n ].it_status = *( unsigned char * ) ( buf + p );
    p += 1;
    cnt[ 4 ]++;
  }
  if ( buf[ 1 ] & 32 )
  {
    map[ n ].ch_sprite = *( unsigned short * ) ( buf + p );
    p += 2;
    map[ n ].ch_status = *( unsigned char * ) ( buf + p );
    p += 1;
    map[ n ].ch_stat_off = *( unsigned char * ) ( buf + p );
    p += 1;
    cnt[ 5 ]++;
  }
  if ( buf[ 1 ] & 64 )
  {
    map[ n ].ch_nr = *( unsigned short * ) ( buf + p );
    p += 2;
    map[ n ].ch_id = *( unsigned short * ) ( buf + p );
    p += 2;
    map[ n ].ch_speed = *( unsigned char * ) ( buf + p );
    p += 1;
    cnt[ 6 ]++;
  }
  if ( buf[ 1 ] & 128 )
  {
    map[ n ].ch_proz = *( unsigned char * ) ( buf + p );
    p += 1;
    cnt[ 7 ]++;
  }
  return p;
}

int sv_setmap3( const unsigned char *buf, int cnt )
{
  int           n, m, p;
  unsigned char tmp;

  n   = ( *( unsigned short * ) ( buf + 1 ) ) & 2047;
  tmp = ( *( unsigned short * ) ( buf + 1 ) ) >> 12;
  if ( n < 0 || n >= TILEX * TILEY )
  {
    std::cerr << "corrupt setmap3!" << std::endl;
    return -1;
  }

  map[ n ].light = tmp;

  for ( m = n + 2, p = 3; m < n + cnt + 2; m += 2, p++ )
  {
    if ( m < TILEX * TILEY )
    {
      tmp = *( unsigned char * ) ( buf + p );

      map[ m ].light     = ( unsigned char ) ( tmp & 15 );
      map[ m - 1 ].light = ( unsigned char ) ( tmp >> 4 );
    }
  }

  return p;
}

void sv_setorigin( const unsigned char *buf )
{
  int x, y, xp, yp, n;

  xp = *( short * ) ( buf + 1 );
  yp = *( short * ) ( buf + 3 );

  for ( y = n = 0; y < TILEY; y++ )
  {
    for ( x = 0; x < TILEX; x++, n++ )
    {
      map[ n ].x = ( unsigned short ) ( x + xp );
      map[ n ].y = ( unsigned short ) ( y + yp );
    }
  }
}

void sv_tick( const unsigned char *buf )
{
  ctick = *( unsigned char * ) ( buf + 1 );
}

void sv_log( const unsigned char *buf, int )
{
  static char text[ 512 ];
  static int  cnt = 0;
  int         n;

  std::memcpy( text + cnt, buf + 1, 15 );

  for ( n = cnt; n < cnt + 15; n++ )
    if ( text[ n ] == 10 )
    {
      text[ n ] = 0;
      std::cerr << text << std::endl;
      cnt = 0;
      return;
    }
  cnt += 15;

  if ( cnt > 500 )
  {
    std::cerr << "sv_log(): cnt too big!" << std::endl;

    text[ cnt ] = 0;
    std::cerr << text << std::endl;
    cnt = 0;
  }
}

void sv_scroll_right( const unsigned char * )
{
  memmove( map, map + 1, sizeof( struct cmap ) * ( TILEX * TILEY - 1 ) );
}

void sv_scroll_left( const unsigned char * )
{
  memmove( map + 1, map, sizeof( struct cmap ) * ( TILEX * TILEY - 1 ) );
}

void sv_scroll_down( const unsigned char * )
{
  memmove( map, map + TILEX, sizeof( struct cmap ) * ( TILEX * TILEY - TILEX ) );
}

void sv_scroll_up( const unsigned char * )
{
  memmove( map + TILEX, map, sizeof( struct cmap ) * ( TILEX * TILEY - TILEX ) );
}

void sv_scroll_leftup( const unsigned char * )
{
  memmove( map + TILEX + 1, map, sizeof( struct cmap ) * ( TILEX * TILEY - TILEX - 1 ) );
}

void sv_scroll_leftdown( const unsigned char * )
{
  memmove( map, map + TILEX - 1, sizeof( struct cmap ) * ( TILEX * TILEY - TILEX + 1 ) );
}

void sv_scroll_rightup( const unsigned char * )
{
  memmove( map + TILEX - 1, map, sizeof( struct cmap ) * ( TILEX * TILEY - TILEX + 1 ) );
}

void sv_scroll_rightdown( const unsigned char * )
{
  memmove( map, map + TILEX + 1, sizeof( struct cmap ) * ( TILEX * TILEY - TILEX - 1 ) );
}

void sv_look1( const unsigned char *buf )
{
  tmplook.worn[ 0 ] = *( unsigned short * ) ( buf + 1 );
  tmplook.worn[ 2 ] = *( unsigned short * ) ( buf + 3 );
  tmplook.worn[ 3 ] = *( unsigned short * ) ( buf + 5 );
  tmplook.worn[ 5 ] = *( unsigned short * ) ( buf + 7 );
  tmplook.worn[ 6 ] = *( unsigned short * ) ( buf + 9 );
  tmplook.worn[ 7 ] = *( unsigned short * ) ( buf + 11 );
  tmplook.worn[ 8 ] = *( unsigned short * ) ( buf + 13 );
  tmplook.autoflag  = *( unsigned char * ) ( buf + 15 );
}

void sv_look2( const unsigned char *buf )
{
  tmplook.worn[ 9 ]  = *( unsigned short * ) ( buf + 1 );  // 1 2
  tmplook.sprite     = *( unsigned short * ) ( buf + 3 );  // 3 4
  tmplook.points     = *( unsigned int * ) ( buf + 5 );    // 5 6 7 8
  tmplook.hp         = *( unsigned int * ) ( buf + 9 );    // 9 10 11 12
  tmplook.worn[ 10 ] = *( unsigned short * ) ( buf + 13 ); // 13 14
}

void sv_look3( const unsigned char *buf )
{
  tmplook.end    = *( unsigned short * ) ( buf + 1 );
  tmplook.a_hp   = *( unsigned short * ) ( buf + 3 );
  tmplook.a_end  = *( unsigned short * ) ( buf + 5 );
  tmplook.nr     = *( unsigned short * ) ( buf + 7 );
  tmplook.id     = *( unsigned short * ) ( buf + 9 );
  tmplook.mana   = *( unsigned short * ) ( buf + 11 );
  tmplook.a_mana = *( unsigned short * ) ( buf + 13 );
}

void sv_look4( const unsigned char *buf )
{
  tmplook.worn[ 1 ]  = *( unsigned short * ) ( buf + 1 );
  tmplook.worn[ 4 ]  = *( unsigned short * ) ( buf + 3 );
  tmplook.extended   = buf[ 5 ];
  tmplook.pl_price   = *( unsigned int * ) ( buf + 6 );
  tmplook.worn[ 11 ] = *( unsigned short * ) ( buf + 10 );
  tmplook.worn[ 12 ] = *( unsigned short * ) ( buf + 12 );
  tmplook.worn[ 13 ] = *( unsigned short * ) ( buf + 14 );
}

void sv_look5( const unsigned char *buf )
{
  int n;

  for ( n = 0; n < 15; n++ )
    tmplook.name[ n ] = buf[ n + 1 ];
  tmplook.name[ 15 ] = 0;

  if ( ! tmplook.extended )
  {
    if ( ! tmplook.autoflag )
    {
      // show_look  = 1;
      // look       = tmplook;
      // look_timer = 10 * TICKS;
    }
    // add_look(tmplook.nr, tmplook.name, tmplook.id);
  }
}

void sv_look6( const unsigned char *buf )
{
  int n, s;

  s = buf[ 1 ];

  for ( n = s; n < std::min( 62, s + 2 ); n++ )
  {
    tmplook.item[ n ]  = *( unsigned short * ) ( buf + 2 + ( n - s ) * 6 );
    tmplook.price[ n ] = *( unsigned int * ) ( buf + 4 + ( n - s ) * 6 );
  }
  if ( n == 62 )
  {
    // show_shop = 1;
    // shop      = tmplook;
  }
}

void sv_settarget( const unsigned char *buf )
{
  pl.attack_cn    = *( unsigned short * ) ( buf + 1 );
  pl.goto_x       = *( unsigned short * ) ( buf + 3 );
  pl.goto_y       = *( unsigned short * ) ( buf + 5 );
  pl.misc_action  = *( unsigned short * ) ( buf + 7 );
  pl.misc_target1 = *( unsigned short * ) ( buf + 9 );
  pl.misc_target2 = *( unsigned short * ) ( buf + 11 );
}

void sv_playsound( const unsigned char *buf )
{
  int  nr, vol, pan;
  char name[ 80 ];

  nr  = *( unsigned int * ) ( buf + 1 );
  vol = *( int * ) ( buf + 5 );
  pan = *( int * ) ( buf + 9 );

  ( void ) vol;
  ( void ) pan;
  sprintf( name, "sfx\\%d.wav", nr );
  // play_sound(name, vol, -pan); // add flag to reverse channels!!
}

void sv_exit( const unsigned char *buf )
{
  int reason;

  reason = *( unsigned int * ) ( buf + 1 );

  if ( reason < 1 || reason > 12 )
  {
    std::cerr << "EXIT: Reason unknown." << std::endl;
  }
  else
  {
    std::cerr << "EXIT: " << logout_reason[ reason ] << std::endl;
  }
  // do_exit = 1;
}

void sv_load( const unsigned char * )
{
  // int load <<--- EXTERN
  // load = *( unsigned int * ) ( buf + 1 );
}

void sv_unique( const unsigned char * )
{
  // unique1 = *( unsigned int * ) ( buf + 1 );
  // unique2 = *( unsigned int * ) ( buf + 5 );
  // save_unique();
}

int sv_ignore( const unsigned char *buf )
{
  int        size, d;
  static int cnt = 0, got = 0, start = 0;

  size = *( unsigned int * ) ( buf + 1 );
  got += size;

  if ( ! start )
  {
    start = time( NULL );
  }

  if ( cnt++ > 16 )
  {
    cnt = 0;
    d   = time( NULL ) - start;
    if ( d == 0 )
    {
      d = 1;
    }
  }

  return size;
}