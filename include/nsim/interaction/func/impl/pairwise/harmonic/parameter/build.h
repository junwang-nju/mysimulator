
#ifndef _Interaction_Func_Implement_Pairwise_Harmonic_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_Harmonic_Parameter_Build_H_

#include "interaction/func/impl/pairwise/harmonic/parameter/name.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterHarmonic(Array1D<Unique64Bit>& prm) {
    Value<T>(prm[HarmonicDualEqStrength])=2*Value<T>(prm[HarmonicEqStrength]);
  }

}

#endif

