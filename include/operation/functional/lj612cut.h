
#ifndef _Functional_LJ612Cut_H_
#define _Functional_LJ612Cut_H_

#include "data/name/parameter-lj612cut.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void FuncLJ612Cut(const T& dsq, const UniqueParameter* prm, T& func){
    if(dsq>prm[LJ612CutCutRSQ].value<T>())   func=0.;
    else {
      T d=sqroot(dsq);
      T d6=dsq*dsq*dsq;
      T ivr6=prm[LJ612CutRealSigma6].value<T>()/d6;
      func=prm[LJ612CutRealStrength].value<T>()*ivr6*(ivr6-2.);
      func-=prm[LJ612CutVc].value<T>();
      func-=prm[LJ612CutKc].value<T>()*(d-prm[LJ612CutCutR].value<T>());
    }
  }

  template <typename T>
  void DiffLJ612Cut(const T& dsq,const UniqueParameter* prm, T& diff){
    if(dsq>prm[LJ612CutCutRSQ].value<T>())   diff=0.;
    else {
      T d=sqroot(dsq);
      T ivd=1./d;
      T ivd2=1./dsq;
      T id6=ivd2*ivd2*ivd2;
      T ivr6=prm[LJ612CutRealSigma6].value<T>()*id6;
      diff=prm[LJ612CutTwlfRealStrength].value<T>()*ivr6*(1.-ivr6)*ivd2;
      diff-=prm[LJ612CutKc].value<T>()*ivd;
    }
  }

  template <typename T>
  void BothLJ612Cut(const T& dsq, const UniqueParameter* prm, T& func, T& diff){
    if(dsq>prm[LJ612CutCutRSQ].value<T>())   func=diff=0.;
    else {
      T d=sqroot(dsq);
      T ivd=1./d;
      T ivd2=1./dsq;
      T id6=ivd2*ivd2*ivd2;
      T ivr6=prm[LJ612CutRealSigma6].value<T>()*id6;
      func=prm[LJ612CutRealStrength].value<T>()*ivr6*(ivr6-2.);
      func-=prm[LJ612CutVc].value<T>();
      func-=prm[LJ612CutKc].value<T>()*(d-prm[LJ612CutCutR].value<T>());
      diff=prm[LJ612CutTwlfRealStrength].value<T>()*ivr6*(1.-ivr6)*ivd2;
      diff-=prm[LJ612CutKc].value<T>()*ivd;
    }
  }

}

#endif

