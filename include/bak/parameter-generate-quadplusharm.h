
#ifndef _Parameter_Generate_Quadruple_plus_Harmonic_H_
#define _Parameter_Generate_Quadruple_plus_Harmonic_H_

#include "vector-base.h"
#include "parameter-name-quadplusharm.h"

namespace std {

  void ParameterGenerateQuadPlusHarm(VectorBase<double>& Param) {
    Param[QuadPlusHarm_FourEqQuadStrength]=
      Param[QuadPlusHarm_EqQuadStrength]*4;
    Param[QuadPlusHarm_DualEqHarmStrength]=
      Param[QuadPlusHarm_EqHarmStrength]*2;
  }

}

#endif

