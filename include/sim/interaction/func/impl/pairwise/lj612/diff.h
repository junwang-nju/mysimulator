
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Diff_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/post-name.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ612(const T* post,const Unique64Bit* P,T* diff) {
    T tmd=post[LJ612IvDistance6];
    *diff=tmd*post[LJ612IvDistanceSQ]
         *(P[LJ612DiffFactorB].value<T>()-P[LJ612DiffFactorA].value<T>()*tmd);
         
  }

}

#endif

