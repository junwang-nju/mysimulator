
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Both_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Both_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void BothHamonic(const T* buf, const Unique64Bit* P, T* func, T* diff) {
    T Dd=buf[HarmonicLength]-P[HarmonicEqLength].value<T>();
    T tmd=P[HarmonicEqStrength].value<T>()*Dd;
    *func=tmd*Dd;
    *diff=(tmd+tmd)*buf[HarmonicIvLength];
  }

}

#endif

