
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Diff_Cosine_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Diff_Cosine_H_

#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void DiffAngleHarmonicCosine(const T* csAng, const Unique64Bit* P, T* diff) {
    T angle=arcCos(*csAng);
    T dangle=angle-P[AngHarmonicEqAngle].value<T>();
    *diff=P[AngHarmonicDualStrength].value<T>()*dangle;
  }

}

#endif

