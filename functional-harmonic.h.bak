
#ifndef _Functional_Harmonic_H_
#define _Functional_Harmonic_H_

#include "vector-base.h"
#include "parameter-id.h"
#include <cmath>

namespace std {

  void FuncFactor_harmonic(const double& dsq, const VectorBase<double>& parm,
                           double& funcfac) {
    double d=sqrt(dsq);
    double Dd=d-parm[harmonic_EqLength];
    funcfac=parm[harmonic_EqStrength]*Dd*Dd;
  }

  void DiffFactor_harmonic(const double& dsq, const VectorBase<double>& parm,
                           double& difffac) {
    double d=sqrt(dsq);
    double Dd=d-parm[harmonic_EqLength];
    difffac=parm[harmonic_DualEqStrength]*Dd/d;
  }

  void BothFactor_harmonic(const double& dsq, const VectorBase<double>& parm,
                           double& funcfac, double& difffac) {
    double d=sqrt(dsq);
    double Dd=d-parm[harmonic_EqLength];
    double tmd=parm[harmonic_EqStrength]*Dd;
    funcfac=tmd*Dd;
    difffac=(tmd+tmd)/d;
  }

}

#endif

