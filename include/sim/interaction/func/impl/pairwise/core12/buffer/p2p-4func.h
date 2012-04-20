
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Buffer_P2P4Func_H_

#include "interaction/func/impl/pairwise/core12/buffer/post-name.h"
#include "interaction/func/impl/pairwise/core12/parameter/name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"

namespace mysimulator {

  template <typename T>
  void Core12Pre2Post4Func(const T* pre,const Unique64Bit*,T* post,bool& flag) {
    T tmd=1./pre[PairwiseDistanceSQ];
    tmd*=tmd;
    post[Core12IvDist12]=tmd*tmd*tmd;
    flag=true;
  }

}

#endif

