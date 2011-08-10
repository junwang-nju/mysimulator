
#ifndef _Interaction_Func_Implement_Core12_Diff_H_
#define _Interaction_Func_Implement_Core12_Diff_H_

#include "interaction/func/impl/core12/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BothCore12(const T& dsq, const Unique64Bit* P, T& func, T& diff) {
    T ivr2=1./dsq;
    T ivr6=ivr2*ivr2*ivr2;
    T ivr12=ivr6*ivr6;
    func=prm[Core12EqStrength].value<T>()*ivr12;
    diff=func+func+func;
    diff+=diff;
    diff+=diff;
    diff*=-ivr2;
  }

}

#endif


