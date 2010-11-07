
#ifndef _Hash_Function_H_
#define _Hash_Function_H_

namespace std {

  unsigned int hash_rs(const char* s, const unsigned int nchar) {
    static const unsigned int b=378551;
    static const unsigned int a=63689;
    unsigned int hash=0, run=a;
    for(unsigned int i=0;i<nchar;++i) { hash*=run; hash+=s[i]; run*=b; }
    return hash;
  }

  unsigned int hash_js(const char* s, const unsigned int nchar) {
    static const unsigned int a=1315423911;
    unsigned int hash=a;
    for(unsigned int i=0;i<nchar;++i) hash^=((hash<<5)+s[i]+(hash>>2));
    return hash;
  }

  unsigned int hash_pjw(const char* s, const unsigned int nchar) {
    static const unsigned int BitsInUnsignedInt=
      static_cast<unsigned int>(sizeof(unsigned int)*8);
    static const unsigned int ThreeQuarters=
      static_cast<unsigned int>((BitsInUnsignedInt*3)/4);
    static const unsigned int OneEighth=
      static_cast<unsigned int>(BitsInUnsignedInt/8);
    static const unsigned int HighBits=
      static_cast<unsigned int>(0xFFFFFFFF)<<(BitsInUnsignedInt-OneEighth);
    unsigned int hash=0, test=0;
    for(unsigned int i=0;i<nchar;++i) {
      hash=(hash<<OneEighth)+s[i];
      if((test=hash&HighBits)!=0)
        hash=((hash^(test>>ThreeQuarters))&(~HighBits));
    }
    return hash;
  }

  unsigned int hash_elf(const char* s, const unsigned int nchar) {
    unsigned int hash=0, x=0;
    for(unsigned int i=0;i<nchar;++i) {
      hash=(hash<<4)+s[i];
      if((x=hash&0xF0000000L)!=0) hash^=(x>>24);
      hash&=~x;
    }
    return hash;
  }

  unsigned int hash_bkdr(const char* s, const unsigned int nchar) {
    unsigned int seed=131; // or 31, 131, 1313, 13131, 131313 etc
    unsigned int hash=0;
    for(unsigned int i=0;i<nchar;++i) { hash*=seed; hash+=s[i]; }
    return hash;
  }

  unsigned int hash_sdbm(const char* s, const unsigned int nchar) {
    unsigned int hash=0;
    for(unsigned int i=0;i<nchar;++i) hash=s[i]+(hash<<6)+(hash<<16)-hash;
    return hash;
  }

  unsigned int hash_djb(const char* s, const unsigned int nchar) {
    unsigned int hash=5381;
    for(unsigned int i=0;i<nchar;++i) hash=((hash<<5)+hash)+s[i];
    return hash;
  }

  unsigned int hash_dek(const char* s, const unsigned int nchar) {
    unsigned int hash=nchar;
    for(unsigned int i=0;i<nchar;++i) hash=((hash<<5)^(hash>>27))^s[i];
    return hash;
  }

  unsigned int hash_bp(const char* s, const unsigned int nchar) {
    unsigned int hash=0;
    for(unsigned int i=0;i<nchar;++i)   hash=(hash<<7)^s[i];
    return hash;
  }

  unsigned int hash_fnv(const char* s, const unsigned int nchar) {
    static const unsigned int fnv_prime=0x811C9DC5;
    unsigned int hash=0;
    for(unsigned int i=0;i<nchar;++i) { hash*=fnv_prime; hash^=s[i]; }
    return hash;
  }

  unsigned int hash_ap(const char* s, const unsigned int nchar) {
    unsigned int hash=0xAAAAAAAA;
    for(unsigned int i=0;i<nchar;++i)
      hash^=((i&1)==0)?((hash<<7)^s[i]*(hash>>3)):
                       (~((hash<<11)+(s[i]^(hash>>5))));
    return hash;
  }

}

#endif
