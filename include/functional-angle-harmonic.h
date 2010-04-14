
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

  void DiffAngHarmonic(
      const double csAng, const double d01, const double d21,
      const VectorBase<double>& Prm, double& diff0, double& diff2) {
    double ang=acos(csAng);
    double dang=ang-Prm[AngHarmonic_EqAngle];
    double ef=Prm[AngHarmonic_DualEqStrength]*dang;
    diff0=ef/d01;
    diff2=ef/d21;
  }

  void BothAngHarmonic(
      const double csAng, const double d01, const double d21,
      const VectorBase<double>& Prm,
      double& func, double& diff0, double& diff2) {
    double ang=acos(csAng);
    double dang=ang-Prm[AngHarmonic_EqAngle];
    func=Prm[AngHarmonic_EqStrength]*dang;
    double ef=func+func;
    func*=dang;
    diff0=ef/d01;
    diff2=ef/d21;
  }

}

#endif
 
