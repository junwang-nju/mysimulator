
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_Update4Func_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_Update4Func_H_

#include "interaction/func/impl/pairwise/dist-coulomb/buffer/name.h"
#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void DistCoulombUpdate4Func(const T* dsq, const Unique64Bit*, T* buffer) {
    buffer[DistCoulombIvDistanceSQ]=1./(*dsq);
  }

}

#endif

