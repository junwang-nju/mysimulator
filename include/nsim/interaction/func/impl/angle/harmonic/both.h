
#ifndef _Interaction_Func_Implment_Angle_Harmonic_Both_H_
#define _Interaction_Func_Implment_Angle_Harmonic_Both_H_

#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "interaction/func/impl/angle/harmonic/buffer/post-name.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BothAngleHarmonic(
      const Array1D<T>& post,const Array1D<Unique64Bit>& P,T* func,T* diff) {
    T dA=post[AngleValue]-P[AngleHarmonicEqAngle].value<T>();
    T tmd=dA*P[AngleHarmonicStrength].value<T>();
    *func=tmd*dA;
    *diff=tmd+tmd;
  }

}

#endif

