
#ifndef _Random_MT_Standard_Allocate_Specification_H_
#define _Random_MT_Standard_Allocate_Specification_H_

#include "random/mt/standard/specification.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  void allocate(MersenneTwister<StandardMT>& R) {
    release(R);
    allocate(R.s,MersenneTwister<StandardMT>::N);
    R.sl=0;
  }

}

#endif

