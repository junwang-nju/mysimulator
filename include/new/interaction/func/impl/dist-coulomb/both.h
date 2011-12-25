
#ifndef _Interaction_Func_Implement_DistCoulomb_Both_H_
#define _Interaction_Func_Implement_DistCoulomb_Both_H_

#include "interaction/func/impl/dist-coulomb/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BothDistCoulomb(const T& dsq,const Unique64Bit* P,T& func,T& diff) {
    T ivd2=1./dsq;
    func=P[dCoulombStrength].value<T>()*ivd2;
    diff=(func+func)*ivd2;
  }

}

#endif

