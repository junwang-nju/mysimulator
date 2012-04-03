
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_Update4Diff_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Buffer_Update4Diff_H_

#include "interaction/func/impl/pairwise/harmonic/buffer/update4func.h"

namespace mysimulator {

  template <typename T>
  void HarmonicBufferUpdate4Diff(const T& dsq, T* buffer) {
    HarmonicBufferUpdate4Func(dsq,buffer);
    buffer[HarmonicIvLength]=1./buffer[HarmonicLength];
  }

}

#endif

