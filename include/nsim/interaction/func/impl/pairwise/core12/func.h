
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Func_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Func_H_

#include "interaction/func/impl/pairwise/core12/parameter/name.h"
#include "interaction/func/impl/pairwise/core12/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void FuncCore12(
      const Array1D<T>& post, const Array1D<Unique64Bit>& P, T* func) {
    *func=Value<T>(P[Core12EqStrength])*post[Core12IvDist12];
  }

}

#endif

