
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Diff_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Diff_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/post-name.h"

namespace mysimulator {

  template <typename T>
  void DiffHarmonic(const T* post,const Unique64Bit* P,T* diff) {
    T Dd=1.-P[HarmonicEqLength].value<T>()*post[HarmonicIvLength];
    *diff=P[HarmonicDualEqStrength].value<T>()*Dd;
  }

}

#endif

