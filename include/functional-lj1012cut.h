
#ifndef _Functional_LJ1012Cut_H_
#define _Functional_LJ1012Cut_H_

#include "parameter-name-lj1012cut.h"
#include <cmath>

namespace std {

  void FuncLJ1012Cut(const double dsq, const UniqueParameter* prm,
                     double& func) {
    if(dsq>prm[LJ1012CutCutRSQ].d)  func=0.;
    else {
      double d=sqrt(dsq);
      double ivr2=prm[LJ1012CutRealRadiusSQ].d/dsq;
      double ivr4=ivr2*ivr2;
      double ivr6=ivr2*ivr4;
      double tmd=ivr6-ivr4;
      func=prm[LJ1012CutRealEnergyDepth].d*ivr6*(5*tmd-ivr4);
      func-=prm[LJ1012CutVc].d;
      func-=prm[LJ1012CutKc].d*(d-prm[LJ1012CutCutR].d);
    }
  }

  void DiffLJ1012Cut(const double dsq, const UniqueParameter* prm,
                     double& diff) {
    if(dsq>prm[LJ1012CutCutRSQ].d)  diff=0.;
    else {
      double d=sqrt(dsq);
      double ivd2=1./dsq;
      double ivd=1./d;
      double ivr2=prm[LJ1012CutRealRadiusSQ].d*ivd2;
      double ivr4=ivr2*ivr2;
      double ivr6=ivr2*ivr4;
      diff=prm[LJ1012CutSixtyRealEnergyDepth].d*ivr6*(ivr4-ivr6)*ivd2;
      diff-=prm[LJ1012CutKc].d*ivd;
    }
  }

  void BothLJ1012Cut(const double dsq, const UniqueParameter* prm,
                     double& func, double& diff) {
    if(dsq>prm[LJ1012CutCutRSQ].d)  func=diff=0.;
    else {
      double d=sqrt(dsq);
      double ivd2=1./dsq;
      double ivd=1./d;
      double ivr2=prm[LJ1012CutRealRadiusSQ].d*ivd2;
      double ivr4=ivr2*ivr2;
      double ivr6=ivr2*ivr4;
      double tmd=ivr6-ivr4;
      func=prm[LJ1012CutRealEnergyDepth].d*ivr6*(5*tmd-ivr4);
      func-=prm[LJ1012CutVc].d;
      func-=prm[LJ1012CutKc].d*(d-prm[LJ1012CutCutR].d);
      diff=-prm[LJ1012CutSixtyRealEnergyDepth].d*ivr6*tmd*ivd2;
      diff-=prm[LJ1012CutKc].d*ivd;
    }
  }

}

#endif

