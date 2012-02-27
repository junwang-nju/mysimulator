
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Diff_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Diff_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void DiffHarmonic(const T& dsq, const Unique64Bit* P, T& diff) {
    T d=sqroot(dsq);
    T Dd=d-P[HarmonicEqLength].value<T>();
    diff=P[HarmonicDualEqStrength].value<T>()*Dd/d;
  }

}

#endif

