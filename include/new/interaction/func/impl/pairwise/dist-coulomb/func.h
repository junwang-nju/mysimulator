
#ifndef _Interaction_Func_Implement_Pairwsie_DistCoulomb_Func_H_
#define _Interaction_Func_Implement_Pairwsie_DistCoulomb_Func_H_

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"
#include "interaction/func/impl/pairwise/dist-coulomb/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void FuncDistCoulomb(const T* buf,const Unique64Bit* P,T* func) {
    *func=P[DistCoulombStrength].value<T>()*buf[DistCoulombIvDistanceSQ];
  }

}

#endif

