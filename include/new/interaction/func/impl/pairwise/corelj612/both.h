
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Both_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Both_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/corelj612/buffer/name.h"
#include "interaction/func/impl/pairwise/lj612/both.h"

namespace mysimulator {

  template <typename T>
  void BothCoreLJ612(const T* buf,const Unique64Bit* P,T* func,T* diff) {
    if(buf[CoreLJ612DistanceSQ]>P[CoreLJ612RadiusSQ].value<T>()) {
      *func=0;
      *diff=0;
    } else {
      BothLJ612(buf,P,func,diff);
      *func+=P[CoreLJ612EqEnergyDepth].value<T>();
    }
  }

}

#endif

