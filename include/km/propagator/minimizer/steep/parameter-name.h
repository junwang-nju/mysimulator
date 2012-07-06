
#ifndef _Propagator_Minimizer_SteepestDescent_Parameter_Name_H_
#define _Propagator_Minimizer_SteepestDescent_Parameter_Name_H_

#include "propagator/minimizer/parameter-name.h"

namespace mysimulator {

  enum SteepMinimizerParameterName {
    SteepMinimizer_MaxStep = Minimizer_MaxStep,
    SteepMinimizer_LineSearchCount = Minimizer_LineSearchCount,
    SteepMinimizer_NumberParameter = Minimizer_NumberParameter
  };

}

#endif

