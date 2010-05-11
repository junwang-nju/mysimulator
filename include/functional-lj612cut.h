
#ifndef _Functional_LJ612Cut_H_
#define _Functional_LJ612Cut_H_

#include "parameter-name-lj612cut.h"
#include <cmath>

namespace std {

  void FuncLJ612Cut(const double dsq, const UniqueParameter* prm,
                    double& func) {
    if(dsq>prm[LJ612CutCutRSQ].d)   func=0.;
    else {
      double d=sqrt(dsq);
      double d6=dsq*dsq*dsq;
      double ivr6=prm[LJ612CutRealSigma6].d/d6;
      func=prm[LJ612CutRealStrength].d*ivr6*(ivr6-2.)-prm[LJ612CutVc].d
          -prm[LJ612CutKc].d*(d-prm[LJ612CutCutR].d);
    }
  }

  void DiffLJ612Cut(const double dsq, const UniqueParameter* prm,
                    double& diff) {
    if(dsq>prm[LJ612CutCutRSQ].d)   diff=0.;
    else {
      double d=sqrt(dsq);
      double ivd=1./d;
      double ivd2=1./dsq;
      double id6=ivd2*ivd2*ivd2;
      double ivr6=prm[LJ612CutRealSigma6].d*id6;
      diff=prm[LJ612CutTwlfRealStrength].d*ivr6*(1.-ivr6)*ivd2
          -prm[LJ612CutKc].d*ivd;
    }
  }

  void BothLJ612Cut(const double dsq, const UniqueParameter* prm,
                    double& func, double& diff) {
    if(dsq>prm[LJ612CutCutRSQ].d)   func=diff=0.;
    else {
      double d=sqrt(dsq);
      double ivd=1./d;
      double ivd2=1./dsq;
      double id6=ivd2*ivd2*ivd2;
      double ivr6=prm[LJ612CutRealSigma6].d*id6;
      func=prm[LJ612CutRealStrength].d*ivr6*(ivr6-2.)-prm[LJ612CutVc].d
          -prm[LJ612CutKc].d*(d-prm[LJ612CutCutR].d);
      diff=prm[LJ612CutTwlfRealStrength].d*ivr6*(1.-ivr6)*ivd2
          -prm[LJ612CutKc].d*ivd;
    }
  }

}

#endif

