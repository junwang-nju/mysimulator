
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Buffer_Update4Func_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Buffer_Update4Func_H_

#include "interaction/func/impl/pairwise/corelj612/buffer/name.h"
#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/buffer/update4func.h"

namespace mysimulator {

  template <typename T>
  void CoreLJ612Update4Func(const T* dsq,const Unique64Bit* P,T* buffer) {
    buffer[CoreLJ612DistanceSQ]=(*dsq);
    if(*dsq<P[CoreLJ612RadiusSQ].value<T>())
      LJ612Update4Func(dsq,P,buffer);
  }

}

#endif

