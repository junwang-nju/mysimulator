
#ifndef _Functional_LJ612Cut_H_
#define _Functional_LJ612Cut_H_

#include "vector-base.h"
#include "parameter-name-lj612cut.h"
#include <cmath>

namespace std {

  void FuncLJ612Cut(const double dsq, const VectorBase<double>& Prm,
                    double& func) {
    double d=sqrt(dsq);
    if(d>Prm[LJ612Cut_CutR])  { func=0.; return; }
    double d6=dsq*dsq*dsq;
    double ivr6=Prm[LJ612Cut_Sigma6]/d6;
    func=Prm[LJ612Cut_Strength]*ivr6*(ivr6-2.)-Prm[LJ612Cut_Vc]
        -Prm[LJ612Cut_Kc]*(d-Prm[LJ612Cut_CutR]);
  }

  void DiffLJ612Cut(const double dsq, const VectorBase<double>& Prm,
                    double& diff) {
    double d=sqrt(dsq);
    if(d>Prm[LJ612Cut_CutR])  { diff=0.; return; }
    double ivd2=1./dsq;
    double ivd=1./d;
    double ivr6=Prm[LJ612Cut_Sigma6]*ivd2*ivd2*ivd2;
    diff=Prm[LJ612Cut_TwlfStrength]*ivr6*(1.-ivr6)*ivd2-Prm[LJ612Cut_Kc]*ivd;
  }

  void BothLJ612Cut(const double dsq, const VectorBase<double>& Prm,
                    double& func, double& diff) {
    double d=sqrt(dsq);
    if(d>Prm[LJ612Cut_CutR])  { func=0.; diff=0.; return; }
    double ivd2=1./dsq;
    double ivd=1./d;
    double ivr6=Prm[LJ612Cut_Sigma6]*ivd2*ivd2*ivd2;
    func=Prm[LJ612Cut_Strength]*ivr6*(ivr6-2.)-Prm[LJ612Cut_Vc]
        -Prm[LJ612Cut_Kc]*(d-Prm[LJ612Cut_CutR]);
    diff=Prm[LJ612Cut_TwlfStrength]*ivr6*(1.-ivr6)*ivd2-Prm[LJ612Cut_Kc]*ivd;
  }

}

#endif
