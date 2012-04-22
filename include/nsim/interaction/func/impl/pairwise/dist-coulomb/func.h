
#ifndef _Interaction_Func_Implement_Pairwsie_DistCoulomb_Func_H_
#define _Interaction_Func_Implement_Pairwsie_DistCoulomb_Func_H_

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/dist-coulomb/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void FuncDistCoulomb(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func) {
    *func=P[DistCoulombStrength].value<T>()*post[DistCoulombIvDistanceSQ];
  }

}

#endif

