
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Both_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Both_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/corelj612/buffer/post-name.h"
#include "interaction/func/impl/pairwise/lj612/both.h"

namespace mysimulator {

  template <typename T>
  void BothCoreLJ612(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func,T* diff) {
    if(post[CoreLJ612DistanceSQ]>P[CoreLJ612RadiusSQ].value<T>()) {
      *func=0;
      *diff=0;
    } else {
      BothLJ612(post,P,func,diff);
      *func+=P[CoreLJ612EnergyDepth].value<T>();
    }
  }

}

#endif

