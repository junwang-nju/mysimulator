
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_P2P4Func_H_

#include "interaction/func/impl/pairwise/lj1012cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/p2p-4func.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void LJ1012CutPre2Post4Func(const T* pre,const Unique64Bit* P,T* buffer,
                              bool& flag) {
    T tmd=pre[PairwiseDistanceSQ];
    buffer[LJ1012CutDistanceSQ]=tmd;
    if(tmd<P[LJ1012CutCutRSQ].value<T>()) {
      LJ1012Pre2Post4Func(pre,P,buffer,flag);
      buffer[LJ1012CutDistance]=sqroot(tmd);
      flag=true;
    } else flag=false;
  }

}

#endif

