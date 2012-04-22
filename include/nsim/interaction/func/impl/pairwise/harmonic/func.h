
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Func_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Func_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void FuncHarmonic(
      const Array1D<T>& post, const Array1D<Unique64Bit>& P, T* func) {
    T Dd=post[HarmonicLength]-P[HarmonicEqLength].value<T>();
    *func=P[HarmonicEqStrength].value<T>()*Dd*Dd;
  }

}

#endif

