
#ifndef _Interaction_Func_Implment_Angle_Harmonic_Parameter_Build_H_
#define _Interaction_Func_Implment_Angle_Harmonic_Parameter_Build_H_

#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterAngleHarmonic(Array1D<Unique64Bit>& prm) {
    prm[AngleHarmonicDualStrength].value<T>()=
         2*prm[AngleHarmonicStrength].value<T>();
  }

}

#endif

