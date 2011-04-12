
#ifndef _Random_MT_DSFMT_Bound_Convert_H_
#define _Random_MT_DSFMT_Bound_Convert_H_

#include "random/mt-dsfmt/interface.h"

namespace mysimulator {

  static const UniqueParameter128Bit SSE2_DoubleTwo(
      *reinterpret_cast<unsigned long long int*>(&dTwo),
      *reinterpret_cast<unsigned long long int*>(&dTwo));
  static const UniqueParameter128Bit SSE2_DoubleNOne(
      *reinterpret_cast<unsigned long long int*>(&dNOne),
      *reinterpret_cast<unsigned long long int*>(&dNOne));
  static const UniqueParameter128Bit SSE2_IntOne(1,1);

  void Convert2Close1Open2(UniqueParameter128Bit& w) {}

  void Convert2Close0Open1(UniqueParameter128Bit& w) {
#ifdef _Have_SSE2
    _mm_storeu_pd(w.d,_mm_add_pd(w,SSE2_DoubleNOne));
#else
    w.d[0]-=1.0;    w.d[1]-=1.0;
#endif
  }

}

#endif

