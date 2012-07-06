
#ifndef _Propagator_Minimizer_ConjugateGradient_Parameter_Name_H_
#define _Propagator_Minimizer_ConjugateGradient_Parameter_Name_H_

#include "propagator/minimizer/parameter-name.h"

namespace mysimulator {

  enum ConjgMinimizerParameterName {
    ConjgMinimizer_MaxStep = Minimizer_MaxStep,
    ConjgMinimizer_LineSearchCount = Minimizer_LineSearchCount,
    ConjgMinimizer_MaxBeta = Minimizer_NumberParameter,
    ConjgMinimizer_NumberParameter
  };

}

#endif

