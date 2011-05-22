
#ifndef _Random_MT_DSFMT_Bound_Convert_H_
#define _Random_MT_DSFMT_Bound_Convert_H_

#include "random/mt-dsfmt/interface.h"

namespace mysimulator {

  static const UniqueParameter128Bit SSE2_DoubleTwo(dTwo,dTwo);
  static const UniqueParameter128Bit SSE2_DoubleNOne(dNOne,dNOne);
  static const UniqueParameter128Bit SSE2_IntOne(1ULL,1ULL);

  void Convert2Close1Open2(UniqueParameter128Bit& w) {}

#ifdef _Have_SSE2

  void Convert2Close0Open1(UniqueParameter128Bit& w) {
    _mm_storeu_pd(w.d,_mm_add_pd(w.sd,SSE2_DoubleNOne));
  }
  void Convert2Open0Close1(UniqueParameter128Bit& w) {
    _mm_storeu_pd(w.d,_mm_sub_pd(SSE2_DoubleTwo,w.sd));
  }
  void Convert2Open0Open1(UniqueParameter128Bit& w) {
    _mm_storeu_si128(&(w.si),_mm_or_si128(w.si,SSE2_IntOne));
    _mm_storeu_pd(w.d,_mm_add_pd(w.sd,SSE2_DoubleNOne));
  }

#else

  void Convert2Close0Open1(UniqueParameter128Bit& w) {
    w.d[0]-=1.0;    w.d[1]-=1.0;
  }
  void Convert2Open0Close1(UniqueParameter128Bit& w) {
    w.d[0]=2.0-w.d[0];  w.d[1]=2.0-w.d[1];
  }
  void Convert2Open0Open1(UniqueParameter128Bit& w) {
    w.ull[0]|=1;      w.ull[1]|=1;
    w.d[0]-=1.0;      w.d[1]-=1.0;
  }

#endif

}

#endif

