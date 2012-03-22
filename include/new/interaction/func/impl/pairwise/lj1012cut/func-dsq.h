
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Func_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Func_DistSQ_H_

#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ1012CutDistSQ(const T* dsq, const Unique64Bit* P, T* func) {
    if((*dsq)>P[LJ1012CutCutRSQ].value<T>())   *func=0;
    else {
      T d=sqroot(*dsq);
      T sgr2=P[LJ1012CutRealRadiusSQ].value<T>()/(*dsq);
      T sgr10;
      sgr10=sgr2*sgr2;
      sgr10*=sgr10;
      sgr10*=sgr2;
      T f;
      f=P[LJ1012CutEqEnergyDepth].value<T>()*sgr10*(5*sgr2-6.);
      f-=P[LJ1012CutVc].value<T>();
      f-=P[LJ1012CutKc].value<T>()*(d-P[LJ1012CutCutR].value<T>());
      *func=f;
    }
  }

}

#endif

