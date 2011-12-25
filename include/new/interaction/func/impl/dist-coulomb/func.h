
#ifndef _Interaction_Func_Implement_DistCoulomb_Func_H_
#define _Interaction_Func_Implement_DistCoulomb_Func_H_

#include "interaction/func/impl/dist-coulomb/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void FuncDistCoulomb(const T& dsq, const Unique64Bit* P, T& func) {
    func=P[dCoulombStrength].value<T>()/dsq;
  }

}

#endif

