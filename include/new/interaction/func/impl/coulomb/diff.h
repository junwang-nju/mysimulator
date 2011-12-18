
#ifndef _Interaction_Func_Implement_Coulomb_Diff_H_
#define _Interaction_Func_Implement_Coulomb_Diff_H_

#include "interaction/func/impl/coulomb/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void DiffCoulomb(const T& dsq, const Unique64Bit* P,T& diff) {
    T d3=dsq*sqroot(dsq);
    diff=-prm[CoulombStrength].value<T>()/d3;
  }

}

#endif

