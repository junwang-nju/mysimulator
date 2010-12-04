
#ifndef _Build_Parameter_Harmonic_H_
#define _Build_Parameter_Harmonic_H_

#include "data/name/harmonic.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterHarmonic(UniqueParameter* prm) {
    copy(prm[HarmonicDualEqStrength],2*prm[HarmonicEqStrength].value<T>());
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterHarmonic(Vector<UniqueParameter>& prm) {
    assert(prm.size>=HarmonicNumberParameter);
    BuildParameterHarmonic<T>(prm.data);
  }

}

#endif

