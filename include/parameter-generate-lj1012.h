
#ifndef _Parameter_Generate_LJ1012_H_
#define _Parameter_Generate_LJ1012_H_

#include "vector-base.h"
#include "parameter-name-lj1012.h"

namespace std {

  void ParameterGenerateLJ1012(VectorBase<double>& Param) {
    Param[LJ1012_EqRadiusSQ]=Param[LJ1012_EqRadius]*Param[LJ1012_EqRadius];
    Param[LJ1012_SixtyEqStrength]=Param[LJ1012_EqStrength]*60;
  }

}

#endif

