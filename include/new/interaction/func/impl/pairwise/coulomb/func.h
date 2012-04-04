
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Func_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Func_H_

#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/coulomb/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void FuncCoulomb(const T* buf, const Unique64Bit* P, T* func) {
    *func=P[CoulombStrength].value<T>()*buf[CoulombIvDistance];
  }

}

#endif

