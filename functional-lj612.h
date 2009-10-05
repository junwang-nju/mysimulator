
#ifndef _Functional_LJ612_H_
#define _Functional_LJ612_H_

#include "var-vector.h"
#include "parameter-id.h"

namespace std {

  void FuncFactor_lj612(const double& dsq, const varVector<double>& parm,
                        double& funcfac) {
    double tmd=parm[lj612_EqRadiusSQ]/dsq;
    tmd*=tmd*tmd;
    funcfac=parm[lj612_EqStrength]*tmd*(tmd-2.);
  }

  void DiffFactor_lj612(const double& dsq, const varVector<double>& parm,
                        double& difffac) {
    double ivd2=1./dsq, tmd=parm[lj612_EqRadiusSQ]*ivd2;
    tmd*=tmd*tmd;
    difffac=parm[lj612_TwlfEqStrength]*tmd*(1.-tmd)*ivd2;
  }

  void BothFactor_lj612(const double& dsq, const varVector<double>& parm,
                        double& funcfac, double& difffac) {
    double ivd2=1./dsq, tmd=parm[lj612_EqRadiusSQ]*ivd2;
    tmd*=tmd*tmd;
    funcfac=parm[lj612_EqStrength]*tmd*(tmd-2.);
    difffac=parm[lj612_TwlfEqStrength]*tmd*(1.-tmd)*ivd2;
  }

}

#endif
