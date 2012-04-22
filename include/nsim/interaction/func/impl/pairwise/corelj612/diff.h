
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Diff_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Diff_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/corelj612/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612/diff.h"

namespace mysimulator {

  template <typename T>
  void DiffCoreLJ612(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* diff) {
    if(post[CoreLJ612DistanceSQ]>P[CoreLJ612RadiusSQ].value<T>()) *diff=0;
    else DiffLJ612(post,P,diff);
  }

}

#endif

