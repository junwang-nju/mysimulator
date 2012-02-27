
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Func_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Func_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ612Cut(const T& dsq, const Unique64Bit* P, T& func) {
    if(dsq>P[LJ612CutCutRSQ].value<T>())  func=0;
    else {
      T d=sqroot(dsq);
      T d6=dsq*dsq*dsq;
      T ivr6=P[LJ612CutRealSigma6].value<T>()/d6;
      func=P[LJ612CutRealStrength].value<T>()*ivr6*(ivr6-2.);
      func-=P[LJ612CutVc].value<T>();
      func-=P[LJ612CutKc].value<T>()*(d-P[LJ612CutCutR].value<T>());
    }
  }

}

#endif

