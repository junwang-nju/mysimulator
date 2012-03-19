
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Diff_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ612(const T* buf,const Unique64Bit* P,T* diff) {
    T tmd=buf[LJ612IvDistance6];
    *diff=tmd*(P[LJ612DiffFactorB].value<T>()-P[LJ612DiffFactorA].value()*tmd)
             *buf[LJ612IvDistanceSQ];
  }

}

#endif

