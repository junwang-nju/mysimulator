
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_P2P4Func_H_

#include "interaction/func/impl/pairwise/coulomb/buffer/post-name.h"
#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "intrinsic-type/square-root.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void CoulombPre2Post4Func(
      const Array1D<T>& pre,const Array1D<Unique64Bit>&,Array1D<T>& post,
      bool& flag) {
    post[CoulombIvDistance]=1./Sqroot(pre[PairwiseDistanceSQ]);
    flag=true;
  }

}


#endif

