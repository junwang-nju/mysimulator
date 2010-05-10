
#ifndef _Parameter_Generate_Harmonic_H_
#define _Parameter_Generate_Harmonic_H_

#include "vector-base.h"
#include "parameter-name-harmonic.h"

namespace std {

  void ParameterGenerateHarmonic(VectorBase<double>& Param) {
    Param[Harmonic_DualEqStrength]=Param[Harmonic_EqStrength]*2;
  }

}

#endif

