
/**
 * @file hash-func.h
 * @brief Functions to generate hash
 */

#ifndef _Hash_Function_H_
#define _Hash_Function_H_

#include "type.h"
#include "error-proc.h"

namespace std {

  uint hash_rs(const char* str, uint nchar) {
    static const uint b=378551;
    static const uint a=63689;
    uint hash=0, run=a;
    for(uint i=0;i<nchar;++i) {
      hash=hash*run+str[i];
      run*=b;
    }
    return hash;
  }

  uint hash_js(const char* str, uint nchar) {
    static const uint a=1315423911;
    uint hash=a;
    for(uint i=0;i<nchar;++i)  hash^=((hash<<5)+str[i]+(hash>>2));
    return hash;
  }

  uint hash_pjw(const char* str, uint nchar) {
    static const uint BitsInUnsignedInt=static_cast<uint>(sizeof(uint)*8);
    static const uint ThreeQuarters=static_cast<uint>((BitsInUnsignedInt*3)/4);
    static const uint OneEighth=static_cast<uint>(BitsInUnsignedInt/8);
    static const uint HighBits=
      static_cast<uint>(0xFFFFFFFF)<<(BitsInUnsignedInt-OneEighth);
    uint hash=0,test=0;
    for(uint i=0;i<nchar;++i) {
      hash=(hash<<OneEighth)+str[i];
      if((test=hash&HighBits)!=0)
        hash=((hash^(test>>ThreeQuarters))&(~HighBits));
    }
    return hash;
  }

  uint hash_elf(const char* str, uint nchar) {
    uint hash=0, x=0;
    for(uint i=0;i<nchar;++i) {
      hash=(hash<<4)+str[i];
      if((x=hash&0xF0000000L)!=0) hash^=(x>>24);
      hash&=~x;
    }
    return hash;
  }

  uint hash_bkdr(const char* str, uint nchar) {
    uint seed=131; // or 31, 131, 1313, 13131, 131313 etc
    uint hash=0;
    for(uint i=0;i<nchar;++i)   hash=(hash*seed)+str[i];
    return hash;
  }

  uint hash_sdbm(const char* str, uint nchar) {
    uint hash=0;
    for(uint i=0;i<nchar;++i)
      hash=str[i]+(hash<<6)+(hash<<16)-hash;
    return hash;
  }

  uint hash_djb(const char* str, uint nchar) {
    uint hash=5381;
    for(uint i=0;i<nchar;++i)
      hash=((hash<<5)+hash)+str[i];
    return hash;
  }

  uint hash_dek(const char* str, uint nchar) {
    uint hash=nchar;
    for(uint i=0;i<nchar;++i)
      hash=((hash<<5)^(hash>>27))^str[i];
    return hash;
  }

  uint hash_bp(const char* str, uint nchar) {
    uint hash=0;
    for(uint i=0;i<nchar;++i)  hash=(hash<<7)^str[i];
    return hash;
  }

  uint hash_fnv(const char* str, uint nchar) {
    static const uint fnv_prime=0x811C9DC5;
    uint hash=0;
    for(uint i=0;i<nchar;++i) {
      hash*=fnv_prime;
      hash^=str[i];
    }
    return hash;
  }

  uint hash_ap(const char* str, uint nchar) {
    uint hash=0xAAAAAAAA;
    for(uint i=0;i<nchar;++i)
      hash^=((i&1)==0)?((hash<<7)^str[i]*(hash>>3)) :
                       (~((hash<<11)+(str[i]^(hash>>5))));
    return hash;
  }

}

#endif

