
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Build_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "intrinsic-type/square.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCoreLJ612(Array1D<Unique64Bit>& prm) {
    T tmd=square(Value<T>(prm[CoreLJ612Radius]));
    Value<T>(prm[CoreLJ612RadiusSQ])=tmd;
    T tmd1=tmd*tmd*tmd;
    tmd=tmd1*Value<T>(prm[CoreLJ612EnergyDepth]);
    Value<T>(prm[CoreLJ612FactorA])=tmd*tmd1;
    Value<T>(prm[CoreLJ612FactorB])=tmd+tmd;
    tmd*=12;
    Value<T>(prm[CoreLJ612DiffFactorA])=tmd*tmd1;
    Value<T>(prm[CoreLJ612DiffFactorB])=tmd;
  }

}

#endif

