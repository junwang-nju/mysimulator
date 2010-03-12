
#ifndef _Functional_Harmonic_H_
#define _Functional_Harmonic_H_

#include "vector-base.h"
#include "parameter-name-harmonic.h"
#include <cmath>

namespace std {

  void FuncHarmonic(const double dsq, const VectorBase<double>& Prm,
                    double& func) {
    double d=sqrt(dsq);
    double Dd=d-Prm[Harmonic_EqLength];
    func=Prm[Harmonic_EqStrength]*Dd*Dd;
  }

  void DiffHarmonic(const double dsq, const VectorBase<double>& Prm,
                    double& diff) {
    double d=sqrt(dsq);
    double Dd=d-Prm[Harmonic_EqLength];
    diff=Prm[Harmonic_DualEqStrength]*Dd/d;
  }

  void BothHarmonic(const double dsq, const VectorBase<double>& Prm,
                    double& func, double& diff) {
    double d=sqrt(dsq);
    double Dd=d-Prm[Harmonic_EqLength];
    double tmd=Prm[Harmonic_EqStrength]*Dd;
    func=tmd*Dd;
    diff=(tmd+tmd)/d;
  }

}

#endif
