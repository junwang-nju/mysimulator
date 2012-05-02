
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Func_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Func_H_

#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "interaction/func/impl/angle/harmonic/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void FuncAngleHarmonic(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func) {
    T dA=post[AngleValue]-Value<T>(P[AngleHarmonicEqAngle]);
    *func=Value<T>(P[AngleHarmonicStrength])*dA*dA;
  }

}

#endif

