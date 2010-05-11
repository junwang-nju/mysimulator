
#ifndef _Functional_LJ612_H_
#define _Functional_LJ612_H_

#include "vector-base.h"
#include "parameter-name-lj612.h"

namespace std {

  void FuncLJ612(const double dsq, const VectorBase<double>& Prm,
                 double& func) {
    double tmd=Prm[LJ612_EqRadiusSQ]/dsq;
    tmd*=tmd*tmd;
    func=Prm[LJ612_EqStrength]*tmd*(tmd-2.);
  }

  void DiffLJ612(const double dsq, const VectorBase<double>& Prm,
                 double& diff) {
    double ivd2=1./dsq;
    double tmd=Prm[LJ612_EqRadiusSQ]*ivd2;
    tmd*=tmd*tmd;
    diff=Prm[LJ612_TwlfEqStrength]*tmd*(1.-tmd)*ivd2;
  }

  void BothLJ612(const double dsq, const VectorBase<double>& Prm,
                 double& func, double& diff) {
    double ivd2=1./dsq;
    double tmd=Prm[LJ612_EqRadiusSQ]*ivd2;
    tmd*=tmd*tmd;
    func=Prm[LJ612_EqStrength]*tmd*(tmd-2.);
    diff=Prm[LJ612_TwlfEqStrength]*tmd*(1.-tmd)*ivd2;
  }

}

#endif
