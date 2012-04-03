
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Buffer_Update4Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Buffer_Update4Func_H_

#include "interaction/func/impl/pairwise/lj1012/buffer/name.h"
#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void LJ1012Update4Func(const T& dsq, const Unique64Bit*, T* buffer) {
    T tmd=1./dsq;
    buffer[LJ1012IvDistanceSQ]=tmd;
    T tmd1=tmd*tmd;
    tmd1*=tmd1;
    buffer[LJ1012IvDistance10]=tmd1*tmd;
  }

}

#endif

