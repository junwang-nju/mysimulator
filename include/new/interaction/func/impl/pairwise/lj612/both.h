
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Both_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Both_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/post-name.h"

namespace mysimulator {

  template <typename T>
  void BothLJ612(const T* post,const Unique64Bit* P,T* func,T* diff) {
    T tmd=post[LJ612IvDistance6];
    *func=tmd*(P[LJ612FactorA].value<T>()*tmd-P[LJ612FactorB].value<T>());
    *diff=tmd*(P[LJ612DiffFactorB].value<T>()-P[LJ612DiffFactorA].value()*tmd)
             *post[LJ612IvDistanceSQ];
  }

}

#endif

