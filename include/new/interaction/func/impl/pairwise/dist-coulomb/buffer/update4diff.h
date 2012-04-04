
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_Update4Diff_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Buffer_Update4Diff_H_

#include "interaction/func/impl/pairwise/dist-coulomb/buffer/update4func.h"

namespace mysimulator {

  template <typename T>
  void DistCoulombUpdate4Diff(const T& dsq, const Unique64Bit* P, T* buffer) {
    update4func(dsq,P,buffer);
  }

}

#endif

