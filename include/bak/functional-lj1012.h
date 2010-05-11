
#ifndef _Functional_LJ1012_H_
#define _Functional_LJ1012_H_

#include "vector-base.h"
#include "parameter-name-lj1012.h"

namespace std {

  void FuncLJ1012(const double dsq, const VectorBase<double>& Prm,
                  double& func) {
    double ivr2=Prm[LJ1012_EqRadiusSQ]/dsq;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr2*ivr4;
    double tmd=ivr6-ivr4;
    func=Prm[LJ1012_EqStrength]*ivr6*(5*tmd-ivr4);
  }

  void DiffLJ1012(const double dsq, const VectorBase<double>& Prm,
                  double& diff) {
    double ivd2=1./dsq;
    double ivr2=Prm[LJ1012_EqRadiusSQ]*ivd2;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr4*ivr2;
    diff=Prm[LJ1012_SixtyEqStrength]*ivr6*(ivr4-ivr6)*ivd2;
  }

  void BothLJ1012(const double dsq, const VectorBase<double>& Prm,
                  double& func, double& diff) {
    double ivd2=1./dsq;
    double ivr2=Prm[LJ1012_EqRadiusSQ]*ivd2;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr4*ivr2;
    double tmd=ivr6-ivr4;
    func=Prm[LJ1012_EqStrength]*ivr6*(5*tmd-ivr4);
    diff=-Prm[LJ1012_SixtyEqStrength]*ivr6*tmd*ivd2;
  }

}

#endif
