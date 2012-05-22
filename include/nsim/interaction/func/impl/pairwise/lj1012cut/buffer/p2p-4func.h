
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Buffer_P2P4Func_H_

#include "interaction/func/impl/pairwise/lj1012cut/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/p2p-4func.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void LJ1012CutPre2Post4Func(
      const Array1D<T>& pre,const Array1D<Unique64Bit>& P,Array1D<T>& buffer,
      bool& flag) {
    T tmd=pre[PairwiseDistanceSQ];
    buffer[LJ1012CutDistanceSQ]=tmd;
    if(tmd<Value<T>(P[LJ1012CutCutRSQ])) {
      LJ1012Pre2Post4Func(pre,P,buffer,flag);
      buffer[LJ1012CutDistance]=Sqroot(tmd);
      flag=true;
    } else flag=false;
  }

}

#endif

