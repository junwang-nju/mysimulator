
#ifndef _Random_MT_DSFMT_Allocate_Specification_H_
#define _Random_MT_DSFMT_Allocate_Specification_H_

#include "random/mt/dsfmt/specification.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <unsigned int Fac>
  void allocate(MersenneTwister<dSFMT,Fac>& R) {
    release(R);
    allocate(R.s,MersenneTwister<dSFMT,Fac>::NStatus);
    R.idx=0;
  }

}

#endif

