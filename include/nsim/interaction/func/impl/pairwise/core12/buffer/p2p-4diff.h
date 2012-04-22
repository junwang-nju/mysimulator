
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Buffer_P2P4Diff_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Buffer_P2P4Diff_H_

#include "interaction/func/impl/pairwise/core12/buffer/post-name.h"
#include "interaction/func/impl/pairwise/core12/parameter/name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void Core12Pre2Post4Diff(
      const Array1D<T>& pre,const Array1D<Unique64Bit>&,Array1D<T>& post,
      bool& flag) {
    T tmd=1./pre[PairwiseDistanceSQ];
    post[Core12IvDistSQ]=tmd;
    tmd*=tmd;
    post[Core12IvDist12]=tmd*tmd*tmd;
    flag=false;
  }

}

#endif

