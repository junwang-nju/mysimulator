
#ifndef _Random_MT_SFMT_Allocate_Specification_H_
#define _Random_MT_SFMT_Allocate_Specification_H_

#include "random/mt/sfmt/specification.h"

namespace mysimulator {

  template <unsigned int Fac>
  void allocate(MersenneTwister<SFMT,Fac>& R) {
    release(R);
    allocate(R.s,MersenneTwister<SFMT,Fac>::N);
    R.idx=0;
  }

}

#endif

