
#ifndef _Propagator_Minimizer_Line_Parameter_Name_H_
#define _Propagator_Minimizer_Line_Parameter_Name_H_

#include "propagator/minimizer/base/parameter-name.h"

namespace mysimulator {

  enum PropagatorMinimizerLineParameterName {
    LineMin_Step = BaseMin_Step,
    LineMin_MaxStep = BaseMin_MaxStep,
    LineMin_SearchScale = BaseMin_SearchScale,
    LineMin_GCalcCount = BaseMin_GCalcCount,
    LineMin_LineTag = BaseMin_NumberParameter,
    LineMin_ConditionTag,
    LineMin_DecreaseFac,
    LineMin_CurvatureFac,
    LineMin_GradThreshold,
    LineMin_NumberParameter
  };

}

#endif

