
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Func_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Func_H_

#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "interaction/func/impl/angle/harmonic/buffer/post-name.h"

namespace mysimulator {

  template <typename T>
  void FuncAngleHarmonic(const T* post,const Unique64Bit* P,T* func) {
    T dA=post[AngleValue]-P[AngleHarmonicEqAngle].value<T>();
    *func=P[AngleHarmonicStrength].value<T>()*dA*dA;
  }

}

#endif

