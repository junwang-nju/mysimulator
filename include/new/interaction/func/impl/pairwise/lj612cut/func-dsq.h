
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Func_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Func_DistSQ_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ612CutDistSQ(const T* dsq, const Unique64Bit* P, T* func) {
    if((*dsq)>P[LJ612CutCutRSQ].value<T>())  *func=0;
    else {
      T d=sqroot(*dsq);
      T d2=*dsq;
      T d6=d2*d2*d2;
      T ivr6=P[LJ612CutRealSigma6].value<T>()/d6;
      T f;
      f=P[LJ612CutRealStrength].value<T>()*ivr6*(ivr6-2.);
      f-=P[LJ612CutVc].value<T>();
      f-=P[LJ612CutKc].value<T>()*(d-P[LJ612CutCutR].value<T>());
      *func=f;
    }
  }

}

#endif

