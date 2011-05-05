
#ifndef _Functional_Harmonic_Parameter_Build_H_
#define _Functional_Harmonic_Parameter_Build_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/harmonic/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterHarmonic(UniqueParameter64Bit* prm) {
    copy(prm[HarmonicDualEqStrength],2*prm[HarmonicEqStrength].value<T>());
  }

}

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterHarmonic(Vector<UniqueParameter64Bit>& prm) {
    assert(prm.size>=HarmonicNumberParameter);
    BuildParameterHarmonic<T>(prm.pdata);
  }

}

#endif

