
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Diff_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Diff_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/corelj612/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612/diff.h"

namespace mysimulator {

  template <typename T>
  void DiffCoreLJ612(const T* post,const Unique64Bit* P,T* diff) {
    if(post[CoreLJ612DistanceSQ]>P[CoreLJ612RadiusSQ].value<T>()) *diff=0;
    else DiffLJ612(post,P,diff);
  }

}

#endif

