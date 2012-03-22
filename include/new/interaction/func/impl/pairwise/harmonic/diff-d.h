
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Diff_Dist_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Diff_Dist_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void DiffHarmonicDist(const T* d, const Unique64Bit* P, T* diff) {
    T rd=*d;
    T Dd=rd-P[HarmonicEqLength].value<T>();
    *diff=P[HarmonicDualEqStrength].value<T>()*Dd/rd;
  }

}

#endif

