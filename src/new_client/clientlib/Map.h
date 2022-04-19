#ifndef MEN_AMONG_GODS_MAP_H
#define MEN_AMONG_GODS_MAP_H

#include <memory>

#include "ClientTypes.h"
#include "MapConstants.h"

namespace MenAmongGods
{
class Map
{
public:
  Map();
  ~Map() = default;

  void setCTick( int newValue );
  void setTicker( std::size_t newValue );

  void tick();

  // Getters / Setters
  unsigned short getX( int index ) const;
  unsigned short getY( int index ) const;
  short int      getBackgroundSprite( int index ) const;
  unsigned char  getLight( int index ) const;
  unsigned int   getFlags( int index ) const;
  unsigned int   getFlags2( int index ) const;
  unsigned short getCharacterSprite( int index ) const;
  unsigned char  getCharacterStatus( int index ) const;
  unsigned char  getCharacterStatOff( int index ) const;
  unsigned char  getCharacterSpeed( int index ) const;
  unsigned short getCharacterId( int index ) const;
  unsigned short getCharacterCrc( int index ) const;
  unsigned char  getCharacterPercentHealth( int index ) const;
  short int      getItemSprite( int index ) const;
  unsigned char  getItemStatus( int index ) const;
  int            getBackground( int index ) const;
  int            getObject1( int index ) const;
  int            getObject2( int index ) const;
  int            getObjectXOffset( int index ) const;
  int            getObjectYOffset( int index ) const;
  int            getOvlXOffset( int index ) const;
  int            getOvlYOffset( int index ) const;
  int            getIdleAnimation( int index ) const;

  void setX( int index, unsigned short newValue );
  void setY( int index, unsigned short newValue );
  void setBackgroundSprite( int index, short int newValue );
  void setLight( int index, unsigned char newValue );
  void setFlags( int index, unsigned int newValue );
  void setFlags2( int index, unsigned int newValue );
  void setCharacterSprite( int index, unsigned short newValue );
  void setCharacterStatus( int index, unsigned char newValue );
  void setCharacterStatOff( int index, unsigned char newValue );
  void setCharacterSpeed( int index, unsigned char newValue );
  void setCharacterId( int index, unsigned short newValue );
  void setCharacterCrc( int index, unsigned short newValue );
  void setCharacterPercentHealth( int index, unsigned char newValue );
  void setItemSprite( int index, short int newValue );
  void setItemStatus( int index, unsigned char newValue );
  void setBackground( int index, int newValue );
  void setObject1( int index, int newValue );
  void setObject2( int index, int newValue );
  void setObjectXOffset( int index, int newValue );
  void setObjectYOffset( int index, int newValue );
  void setOvlXOffset( int index, int newValue );
  void setOvlYOffset( int index, int newValue );
  void setIdleAnimation( int index, int newValue );

  void scrollRight();
  void scrollLeft();
  void scrollDown();
  void scrollUp();
  void scrollLeftUp();
  void scrollLeftDown();
  void scrollRightUp();
  void scrollRightDown();

  cmap getMap( int index ) const;
  void setMap( int index, cmap newValue );

private:
  int speedstep( int n, int d, int s, int update );
  int interpolateItemSprite( unsigned int mapIndex );
  int interpolateCharacterSprite( unsigned int mapIndex );
  int speedo( unsigned int n );

  std::array< cmap, MAPX * MAPY > map_;
  int                             ctick_;
  std::size_t                     ticker_;
};
} // namespace MenAmongGods

#endif