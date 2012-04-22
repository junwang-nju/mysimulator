
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Build_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "intrinsic-type/square.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCoreLJ612(Array1D<Unique64Bit>& prm) {
    T tmd=square(prm[CoreLJ612Radius].value<T>());
    prm[CoreLJ612RadiusSQ].value<T>()=tmd;
    T tmd1=tmd*tmd*tmd;
    tmd=tmd1*prm[CoreLJ612EnergyDepth].value<T>();
    prm[CoreLJ612FactorA].value<T>()=tmd*tmd1;
    prm[CoreLJ612FactorB].value<T>()=tmd+tmd;
    tmd*=12;
    prm[CoreLJ612DiffFactorA].value<T>()=tmd*tmd1;
    prm[CoreLJ612DiffFactorB].value<T>()=tmd;
  }

}

#endif

