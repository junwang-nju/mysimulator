
#ifndef _Interaction_Func_Implement_LJ1012Cut_Both_H_
#define _Interaction_Func_Implement_LJ1012Cut_Both_H_

#include "interaction/func/impl/lj1012cut/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void BothLJ1012Cut(const T& dsq, const Unique64Bit* P, T& fc, T& df) {
    if(dsq>P[LJ1012CutCutRSQ].value<T>())  fc=df=0;
    else {
      T d=sqroot(dsq);
      T ivd2=1./dsq;
      T ivd=1./d;
      T sgr2=P[LJ1012CutRealRadiusSQ].value<T>()*ivd2;
      T sgr10;
      sgr10=sgr2*sgr2;
      sgr10*=sgr10;
      sgr10*=sgr2;
      fc=P[LJ1012CutEqEnergyDepth].value<T>()*sgr10*(5*sgr2-6.);
      fc-=P[LJ1012CutVc].value<T>();
      fc-=P[LJ1012CutKc].value<T>()*(d-P[LJ1012CutCutR].value<T>());
      df=P[LJ1012CutSixtyRealEnergyDepth].value<T>()*sgr10*(1.-sgr2)*ivd2;
      df-=P[LJ1012CutKc].value<T>()*ivd;
    }
  }

}

#endif

