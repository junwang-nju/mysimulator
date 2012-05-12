
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Parameter_Build_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"
#include "intrinsic-type/square.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612(Array1D<Unique64Bit>& prm) {
    T tmd=Square(Value<T>(prm[LJ612EqRadius]));
    T tmd1=tmd*tmd*tmd;
    tmd=tmd1*Value<T>(prm[LJ612EqEnergyDepth]);
    Value<T>(prm[LJ612FactorA])=tmd*tmd1;
    Value<T>(prm[LJ612FactorB])=tmd+tmd;
    tmd*=12;
    Value<T>(prm[LJ612DiffFactorA])=tmd*tmd1;
    Value<T>(prm[LJ612DiffFactorB])=tmd;
  }

}

#endif

