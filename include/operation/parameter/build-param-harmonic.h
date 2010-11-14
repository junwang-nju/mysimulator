
#ifndef _Build_Parameter_Harmonic_H_
#define _Build_Parameter_Harmonic_H_

#include "data/name/parameter-harmonic.h"
#include "data/basic/unique-parameter.h"

namespace std {

  void BuildParameterHarmonic(UniqueParameter* prm) {
    copy(prm[HarmonicDualEqStrength],2*prm[HarmonicEqStrength].d);
  }

}

#include "data/basic/vector.h"

namespace std {

  void BuildParameterHarmonic(Vector<UniqueParameter>& prm) {
    assert(prm.size>=HarmonicNumberParameter);
    BuildParameterHarmonic(prm.data);
  }

}

#endif

