
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Diff_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Diff_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void DiffHarmonic(const T* buf,const Unique64Bit* P,T* diff) {
    T Dd=buf[HarmonicLength]-P[HarmonicEqLength].value<T>();
    *diff=P[HarmonicDualEqStrength].value<T>()*Dd*buf[HarmonicIvLength];
  }

}

#endif

