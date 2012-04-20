
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_P2P4Both_H_

#include "interaction/func/impl/pairwise/lj1012cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/p2p-4both.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void LJ1012CutPre2Post4Both(const T* pre,const Unique64Bit* P,T* post,
                              bool& flag) {
    T tmd=pre[PairwiseDistanceSQ];
    post[LJ1012CutDistanceSQ]=tmd;
    if(tmd<P[LJ1012CutCutRSQ].value<T>()) {
      LJ1012Pre2Post4Both(pre,P,post,flag);
      post[LJ1012CutDistance]=sqroot(tmd);
      post[LJ1012CutIvDistance]=post[LJ1012CutIvDistanceSQ]
                               *post[LJ1012CutDistance];
    } else flag=false;
  }

}

#endif

