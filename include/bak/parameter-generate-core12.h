
#ifndef _Parameter_Generate_Core12_H_
#define _Parameter_Generate_Core12_H_

#include "vector-base.h"
#include "parameter-name-core12.h"

namespace std {

  void ParameterGenerateCore12(VectorBase<double>& Param) {
    Param[Core12_TwlfEqStrength]=12*Param[Core12_EqStrength];
  }

}

#endif

