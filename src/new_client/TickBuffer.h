#ifndef TICK_BUFFER_H
#define TICK_BUFFER_H

#include <array>
#include <cstdint>
#include <memory>

#include "Compressor.h"

class PlayerData;
struct cmap;

class TickBuffer
{
public:
  static constexpr const unsigned int TSIZE = 131072;

  TickBuffer( PlayerData& playerData );
  ~TickBuffer() = default;

  std::uint8_t* getBufferStart() noexcept;
  std::size_t   getAvailableBytes() noexcept;
  bool          receive( const std::array< std::uint8_t, 1024 >* buffer, std::size_t bytesToReceive );
  void          processTicks();

  unsigned int getCTick() const;
  const cmap*  getMap() const;

private:
  int processServerCommand( const std::uint8_t* bufferStart );

  // Server processing commands

  // Declarations to eliminate after refactoring

  void sv_setchar_name1( const unsigned char* buf );
  void sv_setchar_name2( const unsigned char* buf );
  void sv_setchar_name3( const unsigned char* buf );
  void sv_setchar_mode( const unsigned char* buf );
  void sv_setchar_hp( const unsigned char* buf );
  void sv_setchar_endur( const unsigned char* buf );
  void sv_setchar_mana( const unsigned char* buf );
  void sv_setchar_attrib( const unsigned char* buf );
  void sv_setchar_skill( const unsigned char* buf );
  void sv_setchar_ahp( const unsigned char* buf );
  void sv_setchar_aend( const unsigned char* buf );
  void sv_setchar_amana( const unsigned char* buf );
  void sv_setchar_dir( const unsigned char* buf );
  void sv_setchar_pts( const unsigned char* buf );
  void sv_setchar_gold( const unsigned char* buf );
  void sv_setchar_item( const unsigned char* buf );
  void sv_setchar_worn( const unsigned char* buf );
  void sv_setchar_spell( const unsigned char* buf );
  void sv_setchar_obj( const unsigned char* buf );
  int  sv_setmap( const unsigned char* buf, int off );
  int  sv_setmap3( const unsigned char* buf, int cnt );
  void sv_setorigin( const unsigned char* buf );
  void sv_tick( const unsigned char* buf );
  void sv_log( const unsigned char* buf, int font );
  void sv_scroll_right( const unsigned char* buf );
  void sv_scroll_left( const unsigned char* buf );
  void sv_scroll_down( const unsigned char* buf );
  void sv_scroll_up( const unsigned char* buf );
  void sv_scroll_leftup( const unsigned char* buf );
  void sv_scroll_leftdown( const unsigned char* buf );
  void sv_scroll_rightup( const unsigned char* buf );
  void sv_scroll_rightdown( const unsigned char* buf );
  void sv_look1( const unsigned char* buf );
  void sv_look2( const unsigned char* buf );
  void sv_look3( const unsigned char* buf );
  void sv_look4( const unsigned char* buf );
  void sv_look5( const unsigned char* buf );
  void sv_look6( const unsigned char* buf );
  void sv_settarget( const unsigned char* buf );
  void sv_playsound( const unsigned char* buf );
  void sv_exit( const unsigned char* buf );
  void sv_load( const unsigned char* buf );
  void sv_unique( const unsigned char* buf );
  int  sv_ignore( const unsigned char* buf );
  int  skill_cmp( const void* a, const void* b );

  Compressor                        compressor_;
  PlayerData&                       playerData_;
  std::unique_ptr< cmap[] >         map_;
  std::array< std::uint8_t, TSIZE > tickBuffer_;
  unsigned int                      tickSize_;
  unsigned int                      tickStart_;
  unsigned int                      ticksInQueue_;
  unsigned int                      ctick_;
  int                               lastn_;
};

#endif