
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Buffer_Update4Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Buffer_Update4Diff_H_

#include "interaction/func/impl/pairwise/lj612/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void LJ612Update4Diff(const T& dsq, T* buffer) {
    T tmd=1./dsq;
    buffer[LJ612IvDistanceSQ]=tmd;
    buffer[LJ612IvDistance6]=tmd*tmd*tmd;
  }

}

#endif

