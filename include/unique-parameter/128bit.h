
#ifndef _Unique_Parameter_128bit_H_
#define _Unique_Parameter_128bit_H_

#ifdef _Have_SSE2
#include <emmintrin.h>
#endif

#include "io/error.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  union UniqueParameter128Bit {

    typedef UniqueParameter128Bit   Type;

#ifdef _Have_SSE2
    __m128i   si;
    __m128d   sd;
#endif
    long double ld;
    double d[2];
    float f[4];
    unsigned long long ull[2];
    int [4];
    unsigned int u[4];
    void *ptr[4];
    double dvalue;
    float fvalue;
    unsigned long long ullvalue;
    int ivalue;
    unsigned int uvalue;
    void* pvalue;

    UniqueParameter128Bit() { ull[0]=ull[1]=0; }
    UniqueParameter128Bit(const Type&) {
      Error("Copier of UniqueParameter128Bit Disabled!");
    }
    Type& operator=(const Type& P) {
      Error("Operator= for UniqueParameter128Bit Disabled!");
      return *this;
    }
    ~UniqueParameter128Bit() { clearData(); }

    void clearData() {}

  };

}

#endif

