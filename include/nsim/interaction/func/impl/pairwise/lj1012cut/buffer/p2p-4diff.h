
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_P2P4Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_P2P4Diff_H_

#include "interaction/func/impl/pairwise/lj1012cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/p2p-4diff.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void LJ1012CutPre2Post4Diff(
      const Array1D<T>& pre,const Array1D<Unique64Bit>& P,Array1D<T>& post,
      bool& flag) {
    T tmd=pre[PairwiseDistanceSQ];
    post[LJ1012CutDistanceSQ]=tmd;
    if(tmd<Value<T>(P[LJ1012CutCutRSQ])) {
      LJ1012Pre2Post4Diff(pre,P,post,flag);
      post[LJ1012CutIvDistance]=Sqroot(post[LJ1012CutIvDistanceSQ]);
      flag=true;
    } else flag=false;
  }

}

#endif

