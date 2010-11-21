
#ifndef _Functional_LJ1012Cut_H_
#define _Functional_LJ1012Cut_H_

#include "data/name/parameter-lj1012cut.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void FuncLJ1012Cut(const T& dsq, const UniqueParameter* prm, T& func) {
    if(dsq>prm[LJ1012CutCutRSQ].value<T>())  func=0.;
    else {
      T d=sqroot(dsq);
      T sgr2=prm[LJ1012CutRealRadiusSQ].value<T>()/dsq;
      T sgrTEN;
      sgrTEN=sgr2*sgr2;
      sgrTEN*=sgrTEN;
      sgrTEN*=sgr2;
      func=prm[LJ1012CutEqEnergyDepth].value<T>()*sgrTEN*(5*sgr2-6);
      func-=prm[LJ1012CutVc].value<T>();
      func-=prm[LJ1012CutKc].value<T>()*(d-prm[LJ1012CutCutR].value<T>());
    }
  }

  template <typename T>
  void DiffLJ1012Cut(const T& dsq, const UniqueParameter* prm, T& diff) {
    if(dsq>prm[LJ1012CutCutRSQ].value<T>())  diff=0;
    else {
      T ivd2=1./dsq,ivd=sqroot(ivd2);
      T sgr2=prm[LJ1012CutRealRadiusSQ].value<T>()*ivd2;
      T sgrTEN;
      sgrTEN=sgr2*sgr2;
      sgrTEN*=sgrTEN;
      sgrTEN*=sgr2;
      diff=prm[LJ1012CutSixtyRealEnergyDepth].value<T>()*sgrTEN*(1-sgr2)*ivd2;
      diff-=prm[LJ1012CutKc].value<T>()*ivd;
    }
  }

  template <typename T>
  void BothLJ1012Cut(const T& dsq, const UniqueParameter* prm,T& func,T& diff){
    if(dsq>prm[LJ1012CutCutRSQ].value<T>())  func=diff=0;
    else {
      T d=sqroot(dsq);
      T ivd2=1./dsq,ivd=sqroot(ivd2);
      T sgr2=prm[LJ1012CutRealRadiusSQ].value<T>()*ivd2;
      T sgrTEN;
      sgrTEN=sgr2*sgr2;
      sgrTEN*=sgrTEN;
      sgrTEN*=sgr2;
      func=prm[LJ1012CutEqEnergyDepth].value<T>()*sgrTEN*(5*sgr2-6);
      func-=prm[LJ1012CutVc].value<T>();
      func-=prm[LJ1012CutKc].value<T>()*(d-prm[LJ1012CutCutR].value<T>());
      diff=prm[LJ1012CutSixtyRealEnergyDepth].value<T>()*sgrTEN*(1-sgr2)*ivd2;
      diff-=prm[LJ1012CutKc].value<T>()*ivd;
    }
  }

}

#endif

