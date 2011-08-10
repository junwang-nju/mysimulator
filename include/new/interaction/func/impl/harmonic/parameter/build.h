
#ifndef _Interaction_Func_Implement_Harmonic_Parameter_Build_H_
#define _Interaction_Func_Implement_Harmonic_Parameter_Build_H_

#include "unique/64bit/copy.h"
#include "interaction/func/impl/harmonic/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterHarmonic(Unique64Bit* prm) {
    copy(prm[HarmonicDualEqStrength],2*prm[HarmonicEqStrength].value<T>());
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterHarmonic(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>=HarmonicNumberParameters);
    BuildParameterHarmonic<T>(prm.start);
  }

}

#endif

