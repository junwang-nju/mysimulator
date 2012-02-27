
#ifndef _Interaction_Func_Implement_Pairwise_Core12_Func_H_
#define _Interaction_Func_Implement_Pairwise_Core12_Func_H_

#include "interaction/func/impl/pairwise/core12/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void FuncCore12(const T& dsq, const Unique64Bit* P, T& func) {
    T ivr2=1./dsq;
    T ivr6=ivr2*ivr2*ivr2;
    T ivr12=ivr6*ivr6;
    func=P[Core12EqStrength].value<T>()*ivr12;
  }

}

#endif

