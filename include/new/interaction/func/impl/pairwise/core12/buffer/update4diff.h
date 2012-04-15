
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Buffer_Update4Diff_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Buffer_Update4Diff_H_

#include "interaction/func/impl/pairwise/core12/buffer/name.h"
#include "interaction/func/impl/pairwise/core12/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void Core12Update4Diff(const T* dsq,const Unique64Bit*,T* buffer) {
    T tmd=1./(*dsq);
    buffer[Core12IvDistSQ]=tmd;
    tmd*=tmd;
    buffer[Core12IvDist12]=tmd*tmd*tmd;
  }

}

#endif

