
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Func_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Func_H_

#include "interaction/func/impl/pairwise/core12/parameter/name.h"
#include "interaction/func/impl/pairwise/core12/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void FuncCore12(const T* buf, const Unique64Bit* P, T* func) {
    *func=P[Core12EqStrength].value<T>()*buf[Core12IvDist12];
  }

}

#endif

