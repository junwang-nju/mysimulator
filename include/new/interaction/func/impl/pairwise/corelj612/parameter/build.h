
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Build_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCoreLJ612(Unique64Bit* prm) {
    T tmd=square(prm[CoreLJ612Radius].value<T>());
    copy(prm[CoreLJ612RadiusSQ],tmd);
    T tmd1=tmd*tmd*tmd;
    tmd=tmd1*prm[CoreLJ612EnergyDepth].value<T>();
    copy(prm[CoreLJ612FactorA],tmd*tmd1);
    copy(prm[CoreLJ612FactorB],tmd+tmd);
    tmd*=12;
    copy(prm[CoreLJ612DiffFactorA],tmd*tmd1);
    copy(prm[CoreLJ612DiffFactorB],tmd);
  }

  template <typename T>
  void BuildParameterCoreLJ612(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>CoreLJ612NumberParameters);
    BuildParameterCoreLJ612<T>(prm.start);
  }

}

#endif

