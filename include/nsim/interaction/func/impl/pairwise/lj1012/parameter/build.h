
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Parameter_Build_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"
#include "intrinsic-type/square.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012(Array1D<Unique64Bit>& prm) {
    T tmd=Square(Value<T>(prm[LJ1012EqRadius]));
    T tmd1=tmd*tmd;
    T tmd2=tmd1*tmd1*Value<T>(prm[LJ1012EqEnergyDepth]);
    Value<T>(prm[LJ1012FactorA])=tmd2*tmd1*5;
    Value<T>(prm[LJ1012FactorB])=tmd2*tmd*6;
    tmd2*=60;
    Value<T>(prm[LJ1012DiffFactorA])=tmd2*tmd1;
    Value<T>(prm[LJ1012DiffFactorB])=tmd2*tmd;
  }

}

#endif

