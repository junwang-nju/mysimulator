
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012_Parameter_Build_H_

#include "interaction/func/impl/pairwise/lj1012/parameter/name.h"
#include "unique/64bit/copy.h"
#include "intrinsic-type/square.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012(Unique64Bit* prm) {
    T tmd=square(prm[LJ1012EqRadius].value<T>());
    T tmd1=tmd*tmd;
    T tmd2=tmd1*tmd1*prm[LJ1012EqEnergyDepth].value<T>();
    copy(prm[LJ1012FactorA],tmd2*tmd1*5);
    copy(prm[LJ1012FactorB],tmd2*tmd*6);
    tmd2*=60;
    copy(prm[LJ1012DiffFactorA],tmd2*tmd1);
    copy(prm[LJ1012DiffFactorB],tmd2*tmd);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>=LJ1012NumberParameters);
    BuildParameterLJ1012<T>(prm.start);
  }

}

#endif

