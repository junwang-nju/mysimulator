
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Both_Dist_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Both_Dist_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BothHarmonicDist(const T* d,const Unique64Bit* P,T* func,T* diff) {
    T rd=(*d);
    T Dd=rd-P[HarmonicEqLength].value<T>();
    T tmd=P[HarmonicEqStrength].value<T>()*Dd;
    *func=tmd*Dd;
    *diff=(tmd+tmd)/rd;
  }

}

#endif

