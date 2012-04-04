
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Diff_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Diff_H_

#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/coulomb/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void DiffCoulomb(const T* buf, const Unique64Bit* P, T* diff) {
    *diff=P[CoulombStrength].value<T>()*buf[CoulombIvDistanceSQ]
                                       *buf[CoulombIvDistance];
  }

}

#endif

