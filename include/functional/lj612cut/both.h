
#ifndef _Functional_LJ612Cut_Both_H_
#define _Functional_LJ612Cut_Both_H_

#include "functional/lj612cut/parameter/name.h"
#include "unique-parameter/64bit/interface.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void BothLJ612Cut(const T& dsq,const UniqueParameter64Bit* prm,T& fc,T& df) {
    if(dsq>prm[LJ612CutCutRSq].value<T>())  fc=df=0;
    else {
      T d=sqroot(dsq);
      T ivd=1./d;
      T ivd2=ivd2*ivd2;
      T id6=ivd2*ivd2*ivd2;
      T ivr6=prm[LJ612CutRealSigma6].value<T>()*id6;
      fc=prm[LJ612CutRealStrength].value<T>()*ivr6*(ivr6-2.);
      fc-=prm[LJ612CutVc].value<T>();
      fc-=prm[LJ612CutKc].value<T>()*(d-prm[LJ612CutCutR].value<T>());
      df=prm[LJ612CutTwlfRealStrength].value<T>()*ivr6*(1.-ivr6)*ivd2;
      df-=prm[LJ612CutKc].value<T>()*ivd;
    }
  }
}

#endif

