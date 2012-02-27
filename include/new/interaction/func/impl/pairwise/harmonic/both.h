
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Both_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Both_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void BothHarmonic(const T& dsq, const Unique64Bit* P, T& func, T& diff) {
    T d=sqroot(dsq);
    T Dd=d-P[HarmonicEqLength].value<T>();
    T tmd=P[HarmonicEqStrength].value<T>()*Dd;
    func=tmd*Dd;
    diff=(tmd+tmd)/d;
  }

}

#endif

