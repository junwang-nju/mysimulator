
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Diff_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Diff_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/corelj612/buffer/name.h"
#include "interaction/func/impl/pairwise/lj612/diff.h"

namespace mysimulator {

  template <typename T>
  void DiffCoreLJ612(const T* buf,const Unique64Bit* P,T* diff) {
    if(buf[CoreLJ612DistanceSQ]>P[CoreLJ612RadiusSQ].value<T>()) *diff=0;
    else DiffLJ612(buff,P,diff);
  }

}

#endif

