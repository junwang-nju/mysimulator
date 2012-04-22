
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Buffer_P2P4Func_H_

#include "interaction/func/impl/pairwise/lj612/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612/parameter/name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void LJ612Pre2Post4Func(
      const Array1D<T>& pre,const Array1D<Unique64Bit>&,Array1D<T>& post,
      bool& flag) {
    T tmd=1./pre[PairwiseDistanceSQ];
    post[LJ612IvDistance6]=tmd*tmd*tmd;
    flag=true;
  }

}

#endif

