
#ifndef _Build_Parameter_Angle_Harmonic_H_
#define _Build_Parameter_Angle_Harmonic_H_

#include "data/name/angle-harmonic.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterAngleHarmonic(UniqueParameter* prm) {
    assert(IsAvailable(prm));
    copy(prm[AngleHarmonicDualEqStrength],
         2*prm[AngleHarmonicEqStrength].value<T>());
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterAngleHarmonic(Vector<UniqueParameter>& prm) {
    assert(prm.size>=AngleHarmonicNumberParameter);
    BuildParameterAngleHarmonic<T>(prm.data);
  }

}

#endif
