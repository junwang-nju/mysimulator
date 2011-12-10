
#ifndef _Interaction_Func_Implement_LJ1012_Diff_H_
#define _Interaction_Func_Implement_LJ1012_Diff_H_

#include "interaction/func/impl/lj1012/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ1012(const T& dsq, const Unique64Bit* P, T& diff) {
    T ivd2=1./dsq;
    T ivr2=P[LJ1012EqRadiusSQ].value<T>()*ivd2;
    T ivr4=ivr2*ivr2;
    T ivr6=ivr4*ivr2;
    diff=P[LJ1012SixtyEqEnergyDepth].value<T>()*ivr6*(ivr4-ivr6)*ivd2;
  }

}

#endif

