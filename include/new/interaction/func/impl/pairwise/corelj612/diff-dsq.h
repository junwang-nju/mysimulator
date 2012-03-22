
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Diff_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Diff_DistSQ_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/diff-dsq.h"

namespace mysimulator {

  template <typename T>
  void DiffCoreLJ612DistSQ(const T* dsq, const Unique64Bit* P, T* diff) {
    if((*dsq)>P[CoreLJ612RadiusSQ].value<T>()) *diff=0.;
    else DiffLJ612DistSQ(dsq,P,diff);
  }

}

#endif

