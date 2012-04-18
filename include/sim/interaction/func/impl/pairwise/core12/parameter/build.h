
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Parameter_Build_H_

#include "interaction/func/impl/pairwise/core12/parameter/name.h"
#include "unique/64bit/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCore12(Unique64Bit* prm) {
    prm[Core12TwlfEqStrength].value<T>()=12*prm[Core12EqStrength].value<T>();
  }

}

#endif

