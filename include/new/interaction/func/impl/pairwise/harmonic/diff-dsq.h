
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Diff_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Diff_DistSQ_H_

#include "interaction/func/impl/pairwise/harmonic/diff-d.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void DiffHarmonicDistSQ(const T* dsq, const Unique64Bit* P, T* diff) {
    T d=sqroot(*dsq);
    DiffHarmonicDist(&d,P,func);
  }

}

#endif

