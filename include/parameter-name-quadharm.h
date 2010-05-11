
#ifndef _Parameter_Name_QuadrupleHarmonic_H_
#define _Parameter_Name_QuadrupleHarmonic_H_

namespace std {

  enum QuadHarmParameterName {
    QuadHarmEqLength=0,
    QuadHarmEqQuadStrength,
    QuadHarmEqHarmStrength,
    QuadHarmFourEqQuadStrength,
    QuadHarmTwoEqHarmStrength,
    QuadHarmNumberParameter
  };

}

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  void GenerateParameterQuadHarm(UniqueParameter* prm) {
    prm[QuadHarmFourEqQuadStrength]=prm[QuadHarmEqQuadStrength].d*4;
    prm[QuadHarmTwoEqHarmStrength]=prm[QuadHarmEqHarmStrength].d*2;
  }

  void GenerateParameterQuadHarm(Vector<UniqueParameter>& prm) {
    assert(prm.size>=QuadHarmNumberParameter);
    GenerateParameterQuadHarm(prm());
  }

}

#endif

