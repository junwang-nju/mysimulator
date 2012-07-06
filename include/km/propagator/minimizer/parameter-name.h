
#ifndef _Propagator_Minimizer_Parameter_Name_H_
#define _Propagator_Minimizer_Parameter_Name_H_

#include "propagator/minimizer-line/parameter-number-max.h"

namespace mysimulator {

  enum MinimizerParameterName {
    Minimizer_MaxStep=LineMinimizerParameter_MaxNumber,
    Minimizer_LineSearchCount,
    Minimizer_NumberParameter
  };

}

#endif

