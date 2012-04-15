
#ifndef _Interaction_Func_Implment_Angle_Harmonic_Both_H_
#define _Interaction_Func_Implment_Angle_Harmonic_Both_H_

#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "interaction/func/impl/angle/harmonic/buffer/name.h"

namespace mysimulator {

  template <typename T>
  void BothAngleHarmonic(const T* buf,const Unique64Bit* P,T* func,T* diff) {
    T dA=buf[AngleValue]-P[AngleHarmonicEqAngle].value<T>();
    T tmd=dA*P[AngleHarmonicStrength].value<T>();
    *func=tmd*dA;
    *diff=tmd+tmd;
  }

}

#endif

