
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Func_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Func_DistSQ_H_

#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void FuncCoulombDistSQ(const T* dsq, const Unique64Bit* P, T* func) {
    *func=P[CoulombStrength].value<T>()/sqroot(*dsq);
  }

}

#endif

