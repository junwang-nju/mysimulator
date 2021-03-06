
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Buffer_P2P4Both_H_

#include "interaction/func/impl/pairwise/lj612cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/p2p-4both.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void LJ612CutPre2Post4Both(const T* pre, const Unique64Bit* P, T* post,
                             bool& flag) {
    T tmd=pre[PairwiseDistanceSQ];
    post[LJ612CutDistanceSQ]=tmd;
    if(tmd<P[LJ612CutCutRSQ].value<T>()) {
      LJ612Pre2Post4Both(pre,P,post,flag);
      post[LJ612CutDistance]=sqroot(tmd);
      post[LJ612CutIvDistance]=post[LJ612CutDistance]
                              *post[LJ612CutIvDistanceSQ];
    } else flag=false;
  }

}

#endif

