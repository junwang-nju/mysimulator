
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Diff_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Diff_H_

#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "interaction/func/impl/angle/harmonic/buffer/post-name.h"

namespace mysimulator {

  template <typename T>
  void DiffAngleHarmonic(const T* post,const Unique64Bit* P,T* diff) {
    T dA=post[AngleValue]-P[AngleHarmonicEqAngle].value<T>();
    *diff=P[AngleHarmonicDualStrength].value<T>()*dA;
  }

}

#endif

