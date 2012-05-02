
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Both_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Both_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/corelj612/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612/both.h"

namespace mysimulator {

  template <typename T>
  void BothCoreLJ612(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func,T* diff) {
    if(post[CoreLJ612DistanceSQ]>Value<T>(P[CoreLJ612RadiusSQ])) {
      *func=0;
      *diff=0;
    } else {
      BothLJ612(post,P,func,diff);
      *func+=Value<T>(P[CoreLJ612EnergyDepth]);
    }
  }

}

#endif

