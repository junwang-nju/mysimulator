
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Both_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BothLJ612(const T& dsq, const Unique64Bit* P, T& func, T& diff) {
    T ivd2=1./dsq;
    T tmd=P[LJ612EqRadiusSQ].value<T>()*ivd2;
    tmd*=tmd*tmd;
    func=P[LJ612EqEnergyDepth].value<T>()*tmd*(tmd-2.);
    diff=P[LJ612TwlfEnergyDepth].value<T>()*tmd*(1.-tmd)*ivd2;
  }

}

#endif

