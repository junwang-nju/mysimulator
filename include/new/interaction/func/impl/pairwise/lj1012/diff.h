
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Diff_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/post-name.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ1012(const T* post,const Unique64Bit* P,T* diff) {
    T tmd=post[LJ1012IvDistanceSQ];
    *diff=post[LJ1012IvDistance10]*tmd*
         *(P[LJ1012DiffFactorA].value<T>()*tmd-P[LJ1012DiffFactorB].value<T>());
  }

}

#endif

