
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Func_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Func_H_

#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/coulomb/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void FuncCoulomb(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P, T* func) {
    *func=Value<T>(P[CoulombStrength])*post[CoulombIvDistance];
  }

}

#endif

