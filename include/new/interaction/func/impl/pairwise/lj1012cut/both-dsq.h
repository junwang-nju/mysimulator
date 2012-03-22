
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Both_DistSQ_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Both_DistSQ_H_

#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void BothLJ1012CutDistSQ(const T* dsq, const Unique64Bit* P, T* fc, T* df) {
    if((*dsq)>P[LJ1012CutCutRSQ].value<T>())  (*fc)=(*df)=0;
    else {
      T d=sqroot(*dsq);
      T ivd=1./d;
      T ivd2=ivd*ivd;
      T sgr2=P[LJ1012CutRealRadiusSQ].value<T>()*ivd2;
      T sgr10;
      sgr10=sgr2*sgr2;
      sgr10*=sgr10;
      sgr10*=sgr2;
      T func,diff;
      func=P[LJ1012CutEqEnergyDepth].value<T>()*sgr10*(5*sgr2-6.);
      func-=P[LJ1012CutVc].value<T>();
      func-=P[LJ1012CutKc].value<T>()*(d-P[LJ1012CutCutR].value<T>());
      diff=P[LJ1012CutSixtyRealEnergyDepth].value<T>()*sgr10*(1.-sgr2)*ivd2;
      diff-=P[LJ1012CutKc].value<T>()*ivd;
      *fc=func;
      *df=diff;
    }
  }

}

#endif

