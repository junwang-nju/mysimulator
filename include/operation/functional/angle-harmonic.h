
#ifndef _Functional_Angle_Harmonic_H_
#define _Functional_Angle_Harmonic_H_

#include "data/name/angle-harmonic.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void FuncAngleHarmonic(const T& csAng, const UniqueParameter* P, T& func) {
    T angle=arccos(csAng);
    T dangle=angle-P[AngleHarmonicEqAngle].value<T>();
    func=P[AngleHarmonicEqStrength].value<T>()*dangle*dangle;
  }

  template <typename T>
  void DiffAngleHarmonic(const T& csAng, const UniqueParameter* P, T& diff) {
    T angle=arccos(csAng);
    T dangle=angle-P[AngleHarmonicEqAngle].value<T>();
    diff=P[AngleHarmonicDualEqStrength].value<T>()*dangle;
  }

  template <typename T>
  void BothAngleHarmonic(const T& csAng, const UniqueParameter* P,
                         T& func, T& diff) {
    T angle=arccos(csAng);
    T dangle=angle-P[AngleHarmonicEqAngle].value<T>();
    func=P[AngleHarmonicEqStrength].value<T>()*dangle;
    diff=func+func;
    func*=dangle;
  }

}

#endif
