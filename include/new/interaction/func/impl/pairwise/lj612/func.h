
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Func_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/post-name.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ612(const T* post,const Unique64Bit* P,T* func) {
    T tmd=post[LJ612IvDistance6];
    *func=tmd*(P[LJ612FactorA].value<T>()*tmd-P[LJ612FactorB].value<T>());
  }

}

#endif

