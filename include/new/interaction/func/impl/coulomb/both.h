
#ifndef _Interaction_Func_Implement_Coulomb_Both_H_
#define _Interaction_Func_Implement_Coulomb_Both_H_

#include "interaction/func/impl/coulomb/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void BothCoulomb(const T& dsq,const Unique64Bit* P,T& func, T& diff) {
    T ivd2=1./dsq;
    T ivd=sqroot(ivd2);
    func=prm[CoulombStrength].value<T>()*ivd;
    diff=func*ivd2;
  }

}

#endif

