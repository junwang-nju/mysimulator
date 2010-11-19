
#ifndef _Functional_LJ612Cut_H_
#define _Functional_LJ612Cut_H_

#include "data/name/parameter-lj612cut.h"
#include <cmath>

namespace std {

  template <typename T>
  void FuncLJ612Cut(const T& dsq, const UniqueParameter* prm, T& func){
    if(dsq>prm[LJ612CutCutRSQ].d)   func=0.;
    else {
      T d=sqrt(dsq);
      T d6=dsq*dsq*dsq;
      T ivr6=prm[LJ612CutRealSigma6].d/d6;
      func=prm[LJ612CutRealStrength].d*ivr6*(ivr6-2.)-prm[LJ612CutVc].d
          -prm[LJ612CutKc].d*(d-prm[LJ612CutCutR].d);
    }
  }

  template <typename T>
  void DiffLJ612Cut(const T& dsq,const UniqueParameter* prm, T& diff){
    if(dsq>prm[LJ612CutCutRSQ].d)   diff=0.;
    else {
      T d=sqrt(dsq);
      T ivd=1./d;
      T ivd2=1./dsq;
      T id6=ivd2*ivd2*ivd2;
      T ivr6=prm[LJ612CutRealSigma6].d*id6;
      diff=prm[LJ612CutTwlfRealStrength].d*ivr6*(1.-ivr6)*ivd2
          -prm[LJ612CutKc].d*ivd;
    }
  }

  template <typename T>
  void BothLJ612Cut(const T& dsq, const UniqueParameter* prm, T& func, T& diff){
    if(dsq>prm[LJ612CutCutRSQ].d)   func=diff=0.;
    else {
      T d=sqrt(dsq);
      T ivd=1./d;
      T ivd2=1./dsq;
      T id6=ivd2*ivd2*ivd2;
      T ivr6=prm[LJ612CutRealSigma6].d*id6;
      func=prm[LJ612CutRealStrength].d*ivr6*(ivr6-2.)-prm[LJ612CutVc].d
          -prm[LJ612CutKc].d*(d-prm[LJ612CutCutR].d);
      diff=prm[LJ612CutTwlfRealStrength].d*ivr6*(1.-ivr6)*ivd2
          -prm[LJ612CutKc].d*ivd;
    }
  }

}

#endif

