
#ifndef _Functional_LJ1012Cut_H_
#define _Functional_LJ1012Cut_H_

#include "vector-base.h"
#include "parameter-name-lj1012cut.h"
#include <cmath>

namespace std {

  void FuncLJ1012Cut(const double dsq, const VectorBase<double>& Prm,
                     double& func) {
    double d=sqrt(dsq);
    double ivr2=Prm[LJ1012Cut_RadiusSQ]/dsq;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr4*ivr2;
    double tmd=ivr6-ivr4;
    func=Prm[LJ1012Cut_Strength]*ivr6*(5*tmd-ivr4);
    func-=Prm[LJ1012Cut_Vc];
    func-=Prm[LJ1012Cut_Kc]*(d-Prm[LJ1012Cut-CutR]);
  }

  void DiffLJ1012Cut(const double dsq, const VectorBase<double>& Prm,
                     double& diff) {
    double ivd2=1./dsq;
    double ivd=sqrt(ivd2);
    double ivr2=Prm[LJ1012Cut_RadiusSQ]*ivd2;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr2*ivr4;
    diff=Prm[LJ1012Cut_SixtyStrength]*ivr6*(ivr4-ivr6)*ivd2;
    diff-=Prm[LJ1012Cut_Kc]*ivd;
  }

  void BothLJ1012Cut(const double dsq, const VectorBase<double>& Prm,
                     double& func, double& diff) {
    double ivd2=1./dsq;
    double ivd=sqrt(ivd2);
    double ivr2=Prm[LJ1012Cut_RadiusSQ]*ivd2;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr2*ivr4;
    double tmd=ivr6-ivr4;
    func=Prm[LJ1012Cut_Strength]*ivr6*(5*tmd-ivr4);
    func-=Prm[LJ1012Cut_Vc];
    func-=Prm[LJ1012Cut_Kc]*(d-Prm[LJ1012Cut-CutR]);
    diff=-Prm[LJ1012Cut_SixtyStrength]*ivr6*tmd*ivd2;
    diff-=Prm[LJ1012Cut_Kc]*ivd;
  }

}

#endif

