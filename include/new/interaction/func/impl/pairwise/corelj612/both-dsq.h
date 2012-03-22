
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Both_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Both_DistSQ_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/both-dsq.h"

namespace mysimulator {

  template <typename T>
  void BothCoreLJ612DistSQ(const T* dsq, const Unique64Bit* P, T* fc, T* df) {
    if((*dsq)>P[CoreLJ612RadiusSQ].value<T>())   (*fc)=(*df)=0.;
    else {
      BothLJ612(dsq,P,fc,df);
      (*fc)+=P[CoreLJ612EnergyDepth].value<T>();
    }
  }

}

#endif

