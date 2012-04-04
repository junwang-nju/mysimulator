
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Both_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Both_H_

#include "interaction/func/impl/pairwise/dist-coulomb/func.h"

namespace mysimulator {

  template <typename T>
  void BothDistCoulomb(const T* buf,const Unique64Bit* P,T* func,T* diff) {
    FuncDistCoulomb(buf,P,func);
    *diff=(*func)*2*buf[DistCoulombIvDistanceSQ];
  }

}

#endif

