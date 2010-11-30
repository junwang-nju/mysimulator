
#ifndef _Build_Parameter_Quadruple_Plus_Harmonic_H_
#define _Build_Parameter_Quadruple_Plus_Harmonic_H_

#include "data/name/parameter-quad-plus-harmonic.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterQuadPlusHarmonic(UniqueParameter* prm) {
    assert(prm!=NULL);
    copy(prm[QuadHarmonicFourEqQuadStrength],
         prm[QuadHarmonicEqQuadStrength].value<T>()*4);
    copy(prm[QuadHarmonicTwoEqHarmonicStrength],
         prm[QuadHarmonicEqHarmonicStrength].value<T>()*2);
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterQuadPlusHarmonic(Vector<UniqueParameter>& prm) {
    assert(prm.size>=QuadHarmonicNumberParameter);
    BuildParameterQuadPlusHarmonic<T>(prm.data);
  }

}

#endif
