
#ifndef _Parameter_Name_Harmonic_H_
#define _Parameter_Name_Harmonic_H_

namespace std {

  enum HarmonicParameterName {
    HarmonicEqLength=0,
    HarmonicEqStrength,
    HarmonicDualEqStrength,
    HarmonicNumberParameter
  };

}

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  void GenerateParameterHarmonic(UniqueParameter* prm) {
    prm[HarmonicDualEqStrength]=prm[HarmonicEqStrength].d*2;
  }

  void GenerateParameterHarmonic(Vector<UniqueParameter>& prm) {
    assert(prm.size>=HarmonicNumberParameter);
    GenerateParameterHarmonic(prm());
  }

}

#endif

