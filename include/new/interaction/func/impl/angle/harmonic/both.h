
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Both_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Both_H_

#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void BothAngleHarmonic(const T& csAng,const Unique64Bit* P,T& func,T&diff) {
    T angle=arcCos(csAng);
    T dangle=angle-P[AngHarmonicEqAngle].value<T>();
    func=P[AngHarmonicStrength].value<T>()*dangle;
    diff=func+func;
    func*=dangle;
  }

}

#endif

