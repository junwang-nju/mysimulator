
#ifndef _Functional_LJ1012Cut_H_
#define _Functional_LJ1012Cut_H_

#include "data/name/parameter-lj1012cut.h"

namespace std {

  template <typename T>
  void FuncLJ1012Cut(const T& dsq, const UniqueParameter* prm, T& func) {
    if(dsq>prm[LJ1012CutCutRSQ].d)  func=0.;
    else {
      T d=sqrt(dsq);
      T sgr2=prm[LJ1012CutRealRadiusSQ]<T>()/dsq;
      T sgrTEN;
      sgrTEN=sgr2*sgr2;
      sgrTEN*=sgrTEN;
      sgrTEN*=sgr2;
      func=prm[LJ1012CutEqEnergyDepth]<T>()*sgrTEN*(5*sgr2-6);
      func-=prm[LJ1012CutVc]<T>();
      func-=prm[LJ1012CutKc]<T>()*(d-prm[LJ1012CutCutR]<T>());
    }
  }

  void DiffLJ1012Cut(const T& dsq, const UniqueParameter* prm, T& diff) {
    if(dsq>prm[LJ1012CutCutRSQ].d)  diff=0;
    else {
      T ivd2=1./dsq,ivd=sqrt(ivd2);
      T sgr2=prm[LJ1012CutRealRadiusSQ]<T>()*ivd2;
      T sgrTEN;
      sgrTEN=sgr2*sgr2;
      sgrTEN*=sgrTEN;
      sgrTEN*=sgr2;
      diff=prm[LJ1012CutSixtyRealEnergyDepth]<T>()*sgrTEN*(1-sgr2)*ivd2;
      diff-=prm[LJ1012CutKc]<T>()*ivd;
    }
  }

  void BothLJ1012Cut(const T& dsq, const UniqueParameter* prm,T& func,T& diff){
    if(dsq>prm[LJ1012CutCutRSQ].d)  func=diff=0;
    else {
      T ivd2=1./dsq,ivd=sqrt(ivd2);
      T sgr2=prm[LJ1012CutRealRadiusSQ]<T>()*ivd2;
      T sgrTEN;
      sgrTEN=sgr2*sgr2;
      sgrTEN*=sgrTEN;
      sgrTEN*=sgr2;
      func=prm[LJ1012CutEqEnergyDepth]<T>()*sgrTEN*(5*sgr2-6);
      func-=prm[LJ1012CutVc]<T>();
      func-=prm[LJ1012CutKc]<T>()*(d-prm[LJ1012CutCutR]<T>());
      diff=prm[LJ1012CutSixtyRealEnergyDepth]<T>()*sgrTEN*(1-sgr2)*ivd2;
      diff-=prm[LJ1012CutKc]<T>()*ivd;
    }
  }

}

#endif

