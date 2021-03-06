
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Parameter_Build_H_

#include "interaction/func/impl/pairwise/core12/parameter/name.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCore12(Array1D<Unique64Bit>& prm) {
    Value<T>(prm[Core12TwlfEqStrength])=12*Value<T>(prm[Core12EqStrength]);
  }

}

#endif

