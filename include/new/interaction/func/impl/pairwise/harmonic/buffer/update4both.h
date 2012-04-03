
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_Update4Both_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_Update4Both_H_

#include "interaction/func/impl/pairwise/harmonic/buffer/update4diff.h"

namespace mysimulator {

  template <typename T>
  void HarmonicBufferUpdate4Both(const T& dsq, T* buffer) {
    HarmonicBufferUpdate4Diff(dsq,buffer);
  }

}

#endif

