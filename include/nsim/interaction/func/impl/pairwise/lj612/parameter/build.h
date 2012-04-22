
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Parameter_Build_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"
#include "intrinsic-type/square.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612(Array1D<Unique64Bit>& prm) {
    T tmd=square(prm[LJ612EqRadius].value<T>());
    T tmd1=tmd*tmd*tmd;
    tmd=tmd1*prm[LJ612EqEnergyDepth].value<T>();
    prm[LJ612FactorA].value<T>()=tmd*tmd1;
    prm[LJ612FactorB].value<T>()=tmd+tmd;
    tmd*=12;
    prm[LJ612DiffFactorA].value<T>()=tmd*tmd1;
    prm[LJ612DiffFactorB].value<T>()=tmd;
  }

}

#endif

