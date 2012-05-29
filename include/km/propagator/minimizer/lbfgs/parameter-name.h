
#ifndef _Propagator_Minimizer_LBFGS_Parameter_Name_H_
#define _Propagator_Minimizer_LBFGS_Parameter_Name_H_

#include "propagator/minimizer/parameter-name.h"

namespace mysimulator {

  enum LBFGSMinimizerParameterName {
    LBFGSMinimizer_MaxStep = Minimizer_MaxStep,
    LBFGSMinimizer_LineSearchCount = Minimizer_LineSearchCount,
    LBFGSMinimizer_MaxCorrelation = Minimizer_NumberParameter,
    LBFGSMinimizer_NumberParameter
  };

}

#endif

