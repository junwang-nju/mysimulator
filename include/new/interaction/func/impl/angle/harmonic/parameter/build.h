
#ifndef _Interaction_Func_Implment_Angle_Harmonic_Parameter_Build_H_
#define _Interaction_Func_Implment_Angle_Harmonic_Parameter_Build_H_

#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "unique/64bit/copy.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterAngleHarmonic(Unique64Bit* prm) {
    copy(prm[AngHarmonicDualStrength],2*prm[AngHarmonicStrength].value<T>());
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterAngleHarmonic(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>=AngleHarmonicNumberParameters);
    BuildParameterAngleHarmonic<T>(prm.start);
  }

}

#endif

