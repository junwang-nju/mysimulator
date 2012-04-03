
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Buffer_Update4Func_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Buffer_Update4Func_H_

#include "interaction/func/impl/pairwise/core12/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void Core12Update4Func(const T& dsq, T* buffer) {
    T tmd=1./dsq;
    tmd*=tmd;
    buffer[Core12IvDist12]=tmd*tmd*tmd;
  }

}

#endif

