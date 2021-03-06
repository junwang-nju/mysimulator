
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Buffer_P2P4Diff_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Buffer_P2P4Diff_H_

#include "interaction/func/impl/pairwise/corelj612/buffer/post-name.h"
#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/p2p-4diff.h"

namespace mysimulator {

  template  <typename T>
  void CoreLJ612Pre2Post4Diff(const T* pre,const Unique64Bit* P,T* post,
                              bool& flag) {
    T tmd=pre[PairwiseDistanceSQ];
    post[CoreLJ612DistanceSQ]=tmd;
    if(tmd<P[CoreLJ612RadiusSQ].value<T>()) LJ612Pre2Post4Diff(pre,P,post,flag);
    else flag=false;
  }

}

#endif

