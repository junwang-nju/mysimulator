
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Func_Dist_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Func_Dist_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void FuncHarmonicDist(const T* d, const Unique64Bit* P, T* func) {
    T Dd=(*d)-P[HarmonicEqLength].value<T>();
    *func=P[HarmonicEqStrength].value<T>()*Dd*Dd;
  }

}

#endif

