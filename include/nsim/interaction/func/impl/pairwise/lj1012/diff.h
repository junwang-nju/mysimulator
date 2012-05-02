
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Diff_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ1012(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* diff) {
    T tmd=post[LJ1012IvDistanceSQ];
    *diff=post[LJ1012IvDistance10]*tmd
         *(Value<T>(P[LJ1012DiffFactorA])*tmd-Value<T>(P[LJ1012DiffFactorB]));
  }

}

#endif

