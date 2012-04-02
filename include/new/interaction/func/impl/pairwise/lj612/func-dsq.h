
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Func_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Func_DistSQ_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ612DistSQ(const T* dsq, const Unique64Bit* P, T* func) {
    T tmd=P[LJ612EqRadiusSQ].value<T>()/(*dsq);
    tmd*=tmd*tmd;
    *func=P[LJ612EqEnergyDepth].value<T>()*tmd*(tmd-2.);
  }

}

#endif

