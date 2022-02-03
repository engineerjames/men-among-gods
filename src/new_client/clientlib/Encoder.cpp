#include "Encoder.h"

namespace
{
constexpr const char secret[ 256 ] = { "\
Ifhjf64hH8sa,-#39ddj843tvxcv0434dvsdc40G#34Trefc349534Y5#34trecerr943\
5#erZt#eA534#5erFtw#Trwec,9345mwrxm gerte-534lMIZDN(/dn8sfn8&DBDB/D&s\
8efnsd897)DDzD'D'D''Dofs,t0943-rg-gdfg-gdf.t,e95.34u.5retfrh.wretv.56\
9v4#asf.59m(D)/ND/DDLD;gd+dsa,fw9r,x  OD(98snfsf" };
}

std::uint32_t Encoder::xcrypt( std::uint32_t val )
{
  std::uint32_t res = 0;

  res += static_cast< std::uint32_t >( secret[ val & 255 ] );
  res += static_cast< std::uint32_t >( secret[ ( val >> 8 ) & 255 ] ) << 8;
  res += static_cast< std::uint32_t >( secret[ ( val >> 16 ) & 255 ] ) << 16;
  res += static_cast< std::uint32_t >( secret[ ( val >> 24 ) & 255 ] ) << 24;

  res ^= 0x5a7ce52e;

  return res;
}