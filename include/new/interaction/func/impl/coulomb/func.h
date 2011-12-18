
#ifndef _Interaction_Func_Implement_Coulomb_Func_H_
#define _Interaction_Func_Implement_Coulomb_Func_H_

#include "interaction/func/impl/coulomb/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void FuncCoulomb(const T& dsq, const Unique64Bit* P, T& func) {
    func=prm[CoulombStrength].value<T>()/sqroot(dsq);
  }

}

#endif

