
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Diff_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ612(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* diff) {
    T tmd=post[LJ612IvDistance6];
    *diff=tmd*post[LJ612IvDistanceSQ]
         *(Value<T>(P[LJ612DiffFactorB])-Value<T>(P[LJ612DiffFactorA])*tmd);
         
  }

}

#endif

