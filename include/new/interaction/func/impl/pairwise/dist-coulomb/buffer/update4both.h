
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_Update4Both_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_Update4Both_H_

#include "interaction/func/impl/pairwise/dist-coulomb/buffer/update4func.h"

namespace mysimulator {

  template <typename T>
  void DistCoulombUpdate4Both(const T& dsq, const Unique64Bit* P, T* buffer) {
    DistCoulombUpdate4Func(dsq,P,buffer);
  }

}

#endif

