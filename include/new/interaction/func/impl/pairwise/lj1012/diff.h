
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Diff_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"
#include "interaction/func/impl/pairwise/lj1012/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ1012(const T* dsq,const Unique64Bit* P,T* diff) {
    *diff=buf[LJ1012IvDistance10]*buf[LJ1012IvDistanceSQ]
         *(P[LJ1012DiffFactorA].value<T>()*buf[LJ1012IvDistanceSQ]-
           P[LJ1012DiffFactorB].value<T>());
  }

}

#endif

