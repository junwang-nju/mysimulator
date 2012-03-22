
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Func_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Func_DistSQ_H_

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void FuncDistCoulombDistSQ(const T* dsq, const Unique64Bit* P, T* func) {
    *func=P[dCoulombStrength].value<T>()/(*dsq);
  }

}

#endif

