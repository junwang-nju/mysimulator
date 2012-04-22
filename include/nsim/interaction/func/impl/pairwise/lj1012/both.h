
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Both_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BothLJ1012(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func,T* diff) {
    T tmd1=post[LJ1012IvDistanceSQ];
    T tmd2=post[LJ1012IvDistance10];
    *func=tmd2*(P[LJ1012FactorA].value<T>()*tmd1-P[LJ1012FactorB].value<T>());
    *diff=tmd2*tmd1*(P[LJ1012DiffFactorA].value<T>()*tmd1-
                     P[LJ1012DiffFactorB].value<T>());
  }

}

#endif

