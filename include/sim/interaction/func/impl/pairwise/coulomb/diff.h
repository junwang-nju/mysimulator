
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Diff_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Diff_H_

#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/coulomb/buffer/post-name.h"

namespace mysimulator {

  template <typename T>
  void DiffCoulomb(const T* post, const Unique64Bit* P, T* diff) {
    *diff=P[CoulombStrength].value<T>()*post[CoulombIvDistanceSQ]
                                       *post[CoulombIvDistance];
  }

}

#endif

