
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Both_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Both_H_

#include "interaction/func/impl/pairwise/dist-coulomb/func.h"

namespace mysimulator {

  template <typename T>
  void BothDistCoulomb(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func,T* diff) {
    FuncDistCoulomb(post,P,func);
    *diff=(*func)*2*post[DistCoulombIvDistanceSQ];
  }

}

#endif

