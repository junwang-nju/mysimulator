
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_Update4Diff_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Buffer_Update4Diff_H_

#include "interaction/func/impl/pairwise/coulomb/buffer/name.h"
#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void CoulombUpdate4Diff(const T& dsq, const Unique64Bit*, T* buffer) {
    T tmd=1./dsq;
    buffer[CoulombIvDistanceSQ]=tmd;
    buffer[CoulombIvDistance]=sqroot(tmd);
  }

}

#endif

