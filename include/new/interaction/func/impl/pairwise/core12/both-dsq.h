
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Both_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Both_DistSQ_H_

#include "interaction/func/impl/pairwise/core12/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BothCore12DistSQ(const T* dsq, const Unique64Bit* P, T* func, T* diff) {
    T ivr2=1./(*dsq);
    T ivr6=ivr2*ivr2*ivr2;
    T ivr12=ivr6*ivr6;
    T f,d;
    f=P[Core12EqStrength].value<T>()*ivr12;
    *func=f;
    d=f+f+f;
    d+=d;
    d+=d;
    d*=-ivr2;
    *diff=d;
  }

}

#endif


