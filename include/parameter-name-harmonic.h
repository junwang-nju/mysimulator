
#ifndef _Parameter_Name_Harmonic_H_
#define _Parameter_Name_Harmonic_H_

#include "unique-parameter.h"

namespace std {

  enum HarmonicParameterName {
    HarmonicEqLength=0,
    HarmonicEqStrength,
    HarmonicDualEqStrength,
    HarmonicNumberParameter
  };

  void GenerateParameterHarmonic(UniqueParameter* prm) {
    prm[HarmonicDualEqStrength]=prm[HarmonicEqStrength].d*2;
  }

  void GenerateParameterHarmonic(Vector<UniqueParameter>& prm) {
    assert(prm.size>=HarmonicNumberParameter);
    GenerateParameterHarmonic(prm());
  }

}

#endif

