
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_Update4Func_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_Update4Func_H_

#include "intrinsic-type/square-root.h"
#include "interaction/func/impl/pairwise/harmonic/buffer/name.h"
#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void HarmonicBufferUpdate4Func(const T* dsq, const Unique64Bit*, T* buffer) {
    buffer[HarmonicLength]=sqroot(*dsq);
  }

}

#endif

