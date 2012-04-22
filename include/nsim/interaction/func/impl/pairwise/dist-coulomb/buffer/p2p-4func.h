
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_P2P4Func_H_

#include "interaction/func/impl/pairwise/dist-coulomb/buffer/post-name.h"
#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void DistCoulombPre2Post4Func(
      const Array1D<T>& pre,const Array1D<Unique64Bit>&,Array1D<T>& post,
      bool& flag) {
    post[DistCoulombIvDistanceSQ]=1./pre[PairwiseDistanceSQ];
    flag=false;
  }

}

#endif

