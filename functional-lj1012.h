
#ifndef _Functional_LJ1012_H_
#define _Functional_LJ1012_H_

#include "var-vector.h"
#include "parameter-id.h"

namespace std {

  void FuncFactor_lj1012(const double& dsq, const varVector<double>& parm,
                         double& funcfac) {
    double ivr2=parm[lj1012_EqRadiusSQ]/dsq;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr2*ivr4;
    double tmd=ivr6-ivr4;
    funcfac=parm[lj1012_EqStrength]*ivr6*(5*tmd-ivr4);
  }

  void DiffFactor_lj1012(const double& dsq, const varVector<double>& parm,
                         double& difffac) {
    double ivd2=1./dsq;
    double ivr2=parm[lj1012_EqRadiusSQ]*ivd2;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr2*ivr4;
    difffac=parm[lj1012_SixtyEqStrength]*ivr6*(ivr4-ivr6)*ivd2;
  }

  void BothFactor_lj1012(const double& dsq, const varVector<double>& parm,
                         double& funcfac, double& difffac) {
    double ivd2=1./dsq;
    double ivr2=parm[lj1012_EqRadiusSQ]*ivd2;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr2*ivr4;
    double tmd=ivr6-ivr4;
    funcfac=parm[lj1012_EqStrength]*ivr6*(5*tmd-ivr4);
    difffac=-parm[lj1012_SixtyEqStrength]*ivr6*tmd*ivd2;
  }

}

#endif
