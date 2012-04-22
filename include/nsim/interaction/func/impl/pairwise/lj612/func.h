
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Func_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ612(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func) {
    T tmd=post[LJ612IvDistance6];
    *func=tmd*(P[LJ612FactorA].value<T>()*tmd-P[LJ612FactorB].value<T>());
  }

}

#endif

