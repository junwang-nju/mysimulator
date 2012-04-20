
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Parameter_Build_H_

#include "unique/64bit/copy.h"
#include "interaction/func/impl/pairwise/core12/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCore12(Unique64Bit* prm) {
    copy(prm[Core12TwlfEqStrength],12*prm[Core12EqStrength].value<T>());
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCore12(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>=Core12NumberParameters);
    BuildParameterCore12<T>(prm.start);
  }

}

#endif

