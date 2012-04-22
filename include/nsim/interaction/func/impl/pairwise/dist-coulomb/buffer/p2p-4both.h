
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_P2P4Both_H_

#include "interaction/func/impl/pairwise/dist-coulomb/buffer/p2p-4func.h"

namespace mysimulator {

  template <typename T>
  void DistCoulombPre2Post4Both(
      const Array1D<T>& pre, const Array1D<Unique64Bit>& P,Array1D<T>& post,
      bool& flag) {
    DistCoulombPre2Post4Func(pre,P,post,flag);
  }

}

#endif

