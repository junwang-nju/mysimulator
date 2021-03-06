
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Func_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ1012(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func) {
    *func=post[LJ1012IvDistance10]
         *(Value<T>(P[LJ1012FactorA])*post[LJ1012IvDistanceSQ]-
           Value<T>(P[LJ1012FactorB]));
  }

}

#endif

