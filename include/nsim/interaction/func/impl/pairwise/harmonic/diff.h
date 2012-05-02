
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Diff_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Diff_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void DiffHarmonic(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* diff) {
    T Dd=1.-Value<T>(P[HarmonicEqLength])*post[HarmonicIvLength];
    *diff=Value<T>(P[HarmonicDualEqStrength])*Dd;
  }

}

#endif

