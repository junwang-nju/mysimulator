
#ifndef _Interaction_Func_Implement_Pairwise_LJ612_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ612_Parameter_Build_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"
#include "unique/64bit/copy.h"
#include "intrinsic-type/square.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612(Unique64Bit* prm) {
    copy(prm[LJ612EqRadiusSQ],square(prm[LJ612EqRadius].value<T>()));
    copy(prm[LJ612TwlfEnergyDepth],12*prm[LJ612EqEnergyDepth].value<T>());
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>=LJ612NumberParameters);
    BuildParameterLJ612<T>(prm.start);
  }

}

#endif
