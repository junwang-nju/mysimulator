
#ifndef _Parameter_Generate_LJ612_H_
#define _Parameter_Generate_LJ612_H_

#include "vector-base.h"
#include "parameter-name-lj612.h"

namespace std {

  void ParameterGenerateLJ612(VectorBase<double>& Param) {
    Param[LJ612_EqRadiusSQ]=Param[LJ612_EqRadius]*Param[LJ612_EqRadius];
    Param[LJ612_TwlfEqStrength]=Param[LJ612_EqStrength]*12;
  }

}

#endif

