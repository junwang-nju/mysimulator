
#ifndef _Random_MT_DSFMT_Module_Convert_H_
#define _Random_MT_DSFMT_Module_Convert_H_

#include "unique/128bit/interface.h"

namespace mysimulator {

  void Convert2Close1Open2(Unique128Bit&) {}

#ifdef _HAVE_SSE2

  static const Unique128Bit SSE2DoubleTwo(2.,2.);
  static const Unique128Bit SSE2DoubleNOne(-1.,-1.);
  static const Unique128Bit SSE2IntOne(1ULL,1ULL);

  void Convert2Close0Open1(Unique128Bit& w) {
    _mm_storeu_pd(w.dv,_mm_add_pd(_mm_loadu_pd(w.dv),SSE2DoubleNOne.sd));
  }
  void Convert2Open0Close1(Unique128Bit& w) {
    _mm_storeu_pd(w.dv,_mm_sub_pd(SSE2DoubleTwo.sd,_mm_loadu_pd(w.d)));
  }
  void Convert2Open0Open1(Unique128Bit& w) {
    _mm_storeu_si128(&(w.si),_mm_or_si128(_mm_loadu_si128(&(w.si)),SSE2IntOne.si));
    Convert2Close0Open1(w);
  }

#else

  void Convert2Close0Open1(Unique128Bit& w) { w.dv[0]-=1.; w.dv[1]-=1.; }
  void Convert2Open0Close1(Unique128Bit& w) {
    w.dv[0]=2.-w.dv[0]; w.dv[1]=2.-w.dv[1];
  }
  void Convert2Open0Open1(Unique128Bit& w) {
    w.ullv[0]|=1; w.ullv[1]|=1; Convert2Close0Open1(w);
  }

#endif

}

#endif

