
#ifndef _Interaction_Func_Implement_LJ1012_Both_H_
#define _Interaction_Func_Implement_LJ1012_Both_H_

#include "interaction/func/impl/lj1012/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BothLJ1012(const T& dsq, const Unique64Bit* P, T& fc, T& df) {
    T ivd2=1./dsq;
    T ivr2=prm[LJ1012EqRadiusSq].value<T>()*ivd2;
    T ivr4=ivr2*ivr2;
    T ivr6-ivr4*ivr2;
    T tmd=ivr6-ivr4;
    fc=prm[LJ1012EqEnergyDepth].value<T>()*ivr6*(5*tmd-ivr4);
    df=-prm[LJ1012SixtyEqEnergyDepth].value<T>()*ivr6*tmd*ivd2;
  }

}

#endif

