
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Both_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Both_H_

#include "interaction/func/impl/pairwise/coulomb/func.h"

namespace mysimulator {

  template <typename T>
  void BothCoulomb(const T* post, const Unique64Bit* P,T* func,T* diff) {
    FuncCoulomb(post,P,func);
    *diff=(*func)*post[CoulombIvDistanceSQ];
  }

}

#endif

