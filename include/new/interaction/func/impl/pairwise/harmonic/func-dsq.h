
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Func_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Func_DistSQ_H_

#include "interaction/func/impl/pairwise/harmonic/func-d.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void FuncHarmonicDistSQ(const T* dsq, const Unique64Bit* P, T* func) {
    T d=sqroot(*dsq);
    FuncHarmonicDist(&d,P,func);
  }

}

#endif

