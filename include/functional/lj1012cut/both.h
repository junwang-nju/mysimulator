
#ifndef _Functional_LJ1012Cut_Both_H_
#define _Functional_LJ1012Cut_Both_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/lj1012cut/parameter/name.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void BothLJ1012Cut(const T& dsq,const UniqueParameter64Bit* prm,T& fc,T& df){
    if(dsq>prm[LJ1012CutCutRSq].value<T>()) fc=df=0.;
    else {
      T d=sqroot(dsq);
      T ivd2=1./dsq;
      T ivd=1./d;
      T sgr2=prm[LJ1012CutRealRadiusSq].value<T>()*ivd2;
      T sgr10;
      sgr10=sgr2*sgr2;
      sgr10*=sgr10;
      sgr10*=sgr2;
      fc=prm[LJ1012CutEqEnergyDepth].value<T>()*sgr10*(5*sgr2-6.);
      fc-=prm[LJ1012CutVc].value<T>();
      fc-=prm[LJ1012CutKc].value<T>()*(d-prm[LJ1012CutCutR].value<T>());
      df=prm[LJ1012CutSixtyRealEnergyDepth].value<T>()*sgr10*(1.-sgr2)*ivd2;
      df-=prm[LJ1012CutKc].value<T>()*ivd;
    }
  }

}

#endif

