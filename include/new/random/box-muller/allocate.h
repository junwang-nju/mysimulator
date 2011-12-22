
#ifndef _Random_BoxMuller_Allocate_H_
#define _Random_BoxMuller_Allocate_H_

#include "random/box-muller/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <typename UniformRNG>
  void allocate(BoxMuller<UniformRNG>& R) {
    release(R);
    allocate(R.urng);
    allocate(R.s,3);
    R.isSecond=false;
  }

}

#endif

