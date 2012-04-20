
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Buffer_P2P4Func_H_

#include "interaction/func/impl/pairwise/lj612cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/p2p-4func.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void LJ612CutPre2Post4Func(const T* pre, const Unique64Bit* P, T* post,
                             bool& flag) {
    T tmd=pre[PairwiseDistanceSQ];
    post[LJ612CutDistanceSQ]=tmd;
    if(tmd<P[LJ612CutCutRSQ].value<T>()) {
      post[LJ612CutDistance]=sqroot(tmd);
      LJ612Pre2Post4Func(pre,P,post,flag);
    } else flag=false;
  }

}

#endif

