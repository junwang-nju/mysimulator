
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Both_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Both_DistSQ_H_

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BothDistCoulombDistSQ(const T* dsq,const Unique64Bit* P,T* fc,T* df) {
    T ivd2=1./(*dsq);
    *fc=P[dCoulombStrength].value<T>()*ivd2;
    *df=(*func)*(ivd2+ivd2);
  }

}

#endif

