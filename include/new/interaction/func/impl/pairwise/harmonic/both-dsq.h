
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Both_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Both_DistSQ_H_

#include "interaction/func/impl/pairwise/harmonic/both-d.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void BothHarmonicDistSQ(const T* dsq,const Unique64Bit* P,T* func,T* diff) {
    T d=sqroot(*dsq);
    BothHarmonicDist(&d,P,func,diff);
  }

}

#endif

