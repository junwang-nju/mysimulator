
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Both_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Both_H_

#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/coulomb/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void BothCoulomb(const T* buf, const Unique64Bit* P,T* func,T* diff) {
    *func=P[CoulombStrength].value<T>()*buf[CoulombIvDistance];
    *diff=(*func)*buf[CoulombIvDistanceSQ];
  }

}

#endif

