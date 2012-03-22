
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Diff_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Diff_DistSQ_H_

#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void DiffCoulombDistSQ(const T* dsq, const Unique64Bit* P,T* diff) {
    T d3=(*dsq)*sqroot(*dsq);
    *diff=-P[CoulombStrength].value<T>()/d3;
  }

}

#endif

