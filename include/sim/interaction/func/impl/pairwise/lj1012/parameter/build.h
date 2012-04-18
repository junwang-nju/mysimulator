
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Parameter_Build_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"
#include "intrinsic-type/square.h"
#include "unique/64bit/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012(Unique64Bit* prm) {
    T tmd=square(prm[LJ1012EqRadius].value<T>());
    T tmd1=tmd*tmd;
    T tmd2=tmd1*tmd1*prm[LJ1012EqEnergyDepth].value<T>();
    prm[LJ1012FactorA].value<T>()=tmd2*tmd1*5;
    prm[LJ1012FactorB].value<T>()=tmd2*tmd*6;
    tmd2*=60;
    prm[LJ1012DiffFactorA].value<T>()=tmd2*tmd1;
    prm[LJ1012DiffFactorB].value<T>()=tmd2*tmd;
  }

}

#endif

