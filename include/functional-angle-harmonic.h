
#ifndef _Functional_Angle_Harmonic_H_
#define _Functional_Angle_Harmonic_H_

#include "parameter-name-angle-harmonic.h"
#include <cmath>

namespace std {

  void FuncAngleHarmonic(const double csAng, const UniqueParameter* Prm,
                         double& func) {
    double angle=acos(csAng);
    double dangle=angle-Prm[AngleHarmonicEqAngle].d;
    func=Prm[AngleHarmonicEqStrength].d*dangle*dangle;
  }

  void DiffAngleHarmonic(const double csAng, const UniqueParameter* Prm,
                         double& diff) {
    double angle=acos(csAng);
    double dangle=angle-Prm[AngleHarmonicEqAngle].d;
    diff=Prm[AngleHarmonicDualEqStrength].d*dangle;
  }

  void BothAngleHarmonic(const double csAng, const UniqueParameter* Prm,
                         double& func, double& diff) {
    double angle=acos(csAng);
    double dangle=angle-Prm[AngleHarmonicEqAngle].d;
    func=Prm[AngleHarmonicEqStrength].d*dangle;
    diff=func+func;
    func*=dangle;
  }

}

#endif
