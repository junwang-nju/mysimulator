
#ifndef _Parameter_Name_Angle_Harmonic_H_
#define _Parameter_Name_Angle_Harmonic_H_

#include "parameter-name-harmonic.h"

namespace std {

  enum AngleHarmonicParameterName {
    AngleHarmonicEqAngle=HarmonicEqLength,
    AngleHarmonicEqStrength=HarmonicEqStrength,
    AngleHarmonicDualEqStrength=HarmonicDualEqStrength,
    AngleHarmonicNumberParameter=HarmonicNumberParameter
  };

  void GenerateParameterAngleHarmonic(UniqueParameter* prm) {
    GenerateParameterHarmonic(prm);
  }

  void GenerateParameterAngleHarmonic(Vector<UniqueParameter>& prm) {
    GenerateParameterHarmonic(prm);
  }

}

#endif
