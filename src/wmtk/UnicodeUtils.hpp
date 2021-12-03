#pragma once


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../core/NumberUtils.hpp"

#define UTF_INVALID 0xFFFD
#define UTF_SIZ  4

namespace MastTDE {
  static const unsigned char utfbyte[UTF_SIZ + 1] = {0x80, 0, 0xC0, 0xE0, 0xF0};
  static const unsigned char utfmask[UTF_SIZ + 1] = {0xC0, 0x80, 0xE0, 0xF0, 0xF8};
  static const long utfmin[UTF_SIZ + 1] = { 0, 0, 0x80, 0x800, 0x10000};
  static const long utfmax[UTF_SIZ + 1] = { 0x10FFFF, 0x7F, 0x7FF, 0xFFFF, 0x10FFFF};

  long UTF8DecodeByte(const char c, size_t *i){
    for (*i = 0; *i < (UTF_SIZ + 1); ++(*i))
      if (((unsigned char)c & utfmask[*i]) == utfbyte[*i])
	return (unsigned char)c & ~utfmask[*i];
    return 0;
  }


  size_t UTF8Validate(long *u, size_t i){
    if (!IsBetween<long>(*u,(long)utfmin[i],(long)utfmax[i]) || IsBetween<long>(*u,0xD800,0xDFFF))
      *u = UTF_INVALID;
    for (i = 1; *u > utfmax[i]; ++i)
      ;
    return i;
  }

  size_t UTF8Decode(const char* c, long *u, size_t clen){
    size_t i, j, len, type;
    long udecoded;
    *u = UTF_INVALID;
    if(!clen)
      return 0;
    udecoded = UTF8DecodeByte(c[0],&len);
    if(!IsBetween<size_t>(len,1,UTF_SIZ))
      return 1;
    for(i = 1, j = 1; i < clen && j < len; ++i, ++j){
      udecoded = (udecoded << 6) | UTF8DecodeByte(c[i],&type);
      if (type)
	return j;
      
    }
    if (j < len)
      return 0;
    *u = udecoded;
    UTF8Validate(u,len);
    return len;
    
  }
    
}
