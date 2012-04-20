
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Func_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/post-name.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ1012(const T* post,const Unique64Bit* P,T* func) {
    *func=post[LJ1012IvDistance10]
         *(P[LJ1012FactorA].value<T>()*post[LJ1012IvDistanceSQ]-
           P[LJ1012FactorB].value<T>());
  }

}

#endif

