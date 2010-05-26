
#ifndef _Parameter_Name_Centroid_Harmonic_H_
#define _Parameter_Name_Centroid_Harmonic_H_

#include "parameter-name-harmonic.h"

namespace std {

  enum CentroidHarmonicParameterName {
    CentroidHarmonicEqLength=HarmonicEqLength,
    CentroidHarmonicEqStrength=HarmonicEqStrength,
    CentroidHarmonicDualEqStrength=HarmonicDualEqStrength,
    CentroidHarmonicNumberParameter=HarmonicNumberParameter
  };

  void GenerateParameterCentroidHarmonic(UniqueParameter* prm) {
    GenerateParameterHarmonic(prm);
  }

  void GenerateParameterCentroidHarmonic(Vector<UniqueParameter>& prm) {
    GenerateParameterHarmonic(prm);
  }

}

#endif
