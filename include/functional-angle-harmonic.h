
#ifndef _Functional_Angle_Harmonic_H_
#define _Functional_Angle_Harmonic_H_

#include "vector-base.h"
#include "parameter-name-angle-harmonic.h"
#include <cmath>

namespace std {

  void FuncAngHarmonic(const double csAng, const VectorBase<double>& Prm,
                       double& func) {
    double ang=acos(csAng);
    double dang=ang-Prm[AngHarmonic_EqAngle];
    func=Prm[AngHarmonic_EqStrength]*dang*dang;
  }

  void DiffAngHarmonic(const double csAng, const VectorBase<double>& Prm,
                       double& diff) {
    double ang=acos(csAng);
    double dang=ang-Prm[AngHarmonic_EqAngle];
    diff=Prm[AngHarmonic_DualEqStrength]*dang;
  }

  void BothAngHarmonic(const double csAng, const VectorBase<double>& Prm,
                       double& func, double& diff) {
    double ang=acos(csAng);
    double dang=ang-Prm[AngHarmonic_EqAngle];
    func=Prm[AngHarmonic_EqStrength]*dang;
    diff=func+func;
    func*=dang;
  }

}

#endif
 
