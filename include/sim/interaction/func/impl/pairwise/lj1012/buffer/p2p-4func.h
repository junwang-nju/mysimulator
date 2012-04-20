
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Buffer_P2P4Func_H_

#include "interaction/func/impl/pairwise/lj1012/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"

namespace mysimulator {

  template <typename T>
  void LJ1012Pre2Post4Func(const T* pre, const Unique64Bit*, T* post,
                           bool& flag) {
    T tmd=1./pre[PairwiseDistanceSQ];
    post[LJ1012IvDistanceSQ]=tmd;
    T tmd1=tmd*tmd;
    tmd1*=tmd1;
    post[LJ1012IvDistance10]=tmd1*tmd;
    flag=false;
  }

}

#endif

