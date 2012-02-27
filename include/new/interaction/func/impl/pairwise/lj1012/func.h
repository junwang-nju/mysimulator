
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Func_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ1012(const T& dsq, const Unique64Bit* P, T& func) {
    T ivr2=P[LJ1012EqRadiusSQ].value<T>()/dsq;
    T ivr4=ivr2*ivr2;
    T ivr6=ivr4*ivr2;
    T tmd=ivr6-ivr4;
    func=P[LJ1012EqEnergyDepth].value<T>()*ivr6*(5*tmd-ivr4);
  }

}

#endif

