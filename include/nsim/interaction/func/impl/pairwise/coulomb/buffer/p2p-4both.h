
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_P2P4Both_H_

#include "interaction/func/impl/pairwise/coulomb/buffer/p2p-4diff.h"

namespace mysimulator {

  template <typename T>
  void CoulombPre2Post4Both(
      const Array1D<T>& pre,const Array1D<Unique64Bit>& P,Array1D<T>& post,
      bool& flag) {
    CoulombPre2Post4Diff(pre,P,post,flag);
  }

}

#endif

