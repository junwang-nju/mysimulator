
#ifndef _Propagator_Minimizer_Line_Parameter_Name_H_
#define _Propagator_Minimizer_Line_Parameter_Name_H_

#include "propagator/minimizer/parameter-name.h"

namespace mysimulator {

  enum PropagatorMinimizerLineParameterName {
    PropagatorLineMin_Step = PropagatorMin_Step,
    PropagatorLineMin_SearchScale = PropagatorMin_SearchScale,
    PropagatorLineMin_GCalcCount = PropagatorMin_GCalcCount,
    PropagatorLineMin_LineTag = PropagatorMin_NumberParameter,
    PropagatorLineMin_DecreaseFac,
    PropagatorLineMin_CurvatureFac,
    PropagatorLineMin_GradThreshold,
    PropagatorLineMin_LineSearchCount,
    PropagatorLineMin_NumberParameter
  };

}

#endif

